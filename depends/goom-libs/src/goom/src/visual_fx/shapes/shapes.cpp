#include "shapes.h"

//#undef NO_LOGGING

#include "color/color_adjustment.h"
#include "color/random_color_maps.h"
#include "color/random_color_maps_manager.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "logging.h"
#include "point2d.h"
#include "shape_parts.h"
#include "utils/math/goom_rand_base.h"

namespace GOOM::VISUAL_FX::SHAPES
{

using COLOR::ColorAdjustment;
using COLOR::RandomColorMaps;
using COLOR::RandomColorMapsManager;
using DRAW::IGoomDraw;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::MATH::IGoomRand;

Shape::Shape(IGoomDraw& draw,
             const IGoomRand& goomRand,
             const PluginInfo& goomInfo,
             RandomColorMapsManager& colorMapsManager,
             const Params& params) noexcept
  : m_draw{draw},
    m_goomRand{goomRand},
    m_goomInfo{goomInfo},
    m_colorMapsManager{colorMapsManager},
    m_shapeParts{GetInitialShapeParts(params)}
{
}

auto Shape::GetInitialShapeParts(const Params& params) noexcept -> std::vector<ShapePart>
{
  auto shapeParts = std::vector<ShapePart>{};

  for (auto i = 0U; i < NUM_SHAPE_PARTS; ++i)
  {
    static constexpr auto T_MIN_MAX_LERP = 0.5F;
    const auto shapePartParams           = ShapePart::Params{
        i,
        NUM_SHAPE_PARTS,
        params.minRadiusFraction,
        params.maxRadiusFraction,
        params.minShapeDotRadius,
        params.maxShapeDotRadius,
        params.maxNumShapePaths,
        T_MIN_MAX_LERP,
        params.zoomMidpoint,
        params.minNumShapePathSteps,
        params.maxNumShapePathSteps,
    };
    shapeParts.emplace_back(m_draw, m_goomRand, m_goomInfo, m_colorMapsManager, shapePartParams);
  }

  return shapeParts;
}

auto Shape::SetWeightedMainColorMaps(
    const std::shared_ptr<const RandomColorMaps> weightedMaps) noexcept -> void
{
  Expects(AllColorMapsValid());
  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [&weightedMaps](ShapePart& shapePart)
                { shapePart.SetWeightedMainColorMaps(weightedMaps); });
  Ensures(AllColorMapsValid());
}

auto Shape::SetWeightedLowColorMaps(
    const std::shared_ptr<const RandomColorMaps> weightedMaps) noexcept -> void
{
  Expects(AllColorMapsValid());
  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [&weightedMaps](ShapePart& shapePart)
                { shapePart.SetWeightedLowColorMaps(weightedMaps); });
  Ensures(AllColorMapsValid());
}

auto Shape::SetWeightedInnerColorMaps(
    const std::shared_ptr<const RandomColorMaps> weightedMaps) noexcept -> void
{
  Expects(AllColorMapsValid());
  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [&weightedMaps](ShapePart& shapePart)
                { shapePart.SetWeightedInnerColorMaps(weightedMaps); });
  Ensures(AllColorMapsValid());
}

auto Shape::AllColorMapsValid() const noexcept -> bool
{
  for (const auto& shapePart : m_shapeParts)
  {
    const auto numShapePaths = shapePart.GetNumShapePaths();
    for (auto shapePathNum = 0U; shapePathNum < numShapePaths; ++shapePathNum)
    {
      assert(shapePart.GetShapePath(shapePathNum).GetColorInfo().mainColorMapId.IsSet());
      assert(shapePart.GetShapePath(shapePathNum).GetColorInfo().lowColorMapId.IsSet());
      assert(shapePart.GetShapePath(shapePathNum).GetColorInfo().innerColorMapId.IsSet());
    }
  }
  return true;
}

auto Shape::SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void
{
  if (static constexpr auto PROB_ACCEPT_NEW_MIDPOINT = 0.8F;
      not m_goomRand.ProbabilityOf(PROB_ACCEPT_NEW_MIDPOINT))
  {
    return;
  }

  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [&zoomMidpoint](ShapePart& shapePart)
                { shapePart.SetShapePathsTargetPoint(zoomMidpoint); });
}

auto Shape::SetShapePathsMinMaxNumSteps(const uint32_t shapePathsMinNumSteps,
                                        const uint32_t shapePathsMaxNumSteps) noexcept -> void
{
  std::for_each(
      begin(m_shapeParts),
      end(m_shapeParts),
      [&shapePathsMinNumSteps, &shapePathsMaxNumSteps](ShapePart& shapePart)
      { shapePart.SetShapePathsMinMaxNumSteps(shapePathsMinNumSteps, shapePathsMaxNumSteps); });
}

auto Shape::Start() noexcept -> void
{
  SetFixedShapeNumSteps();
  StartChromaChangeOnOffTimer();

  std::for_each(
      begin(m_shapeParts), end(m_shapeParts), [](ShapePart& shapePart) { shapePart.Start(); });

  Ensures(AllColorMapsValid());
}

auto Shape::Draw() noexcept -> void
{
  const auto shapePartParams = ShapePart::DrawParams{
      GetBrightnessAttenuation(),
      FirstShapePathAtMeetingPoint(),
      m_varyDotRadius,
      GetCurrentMeetingPointColors(),
  };
  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [&shapePartParams](ShapePart& shapePart) { shapePart.Draw(shapePartParams); });

  if (FirstShapePathAtMeetingPoint())
  {
    m_meetingPointColorsT.Increment();
  }
}

inline auto Shape::GetCurrentMeetingPointColors() const noexcept -> ShapePath::ShapePathColors
{
  return {
      m_colorMapsManager.GetColorMap(m_meetingPointMainColorId).GetColor(m_meetingPointColorsT()),
      m_colorMapsManager.GetColorMap(m_meetingPointLowColorId).GetColor(m_meetingPointColorsT()),
  };
}

inline auto Shape::GetBrightnessAttenuation() const noexcept -> float
{
  if (not FirstShapePathsCloseToMeeting())
  {
    return 1.0F;
  }

  const auto distanceFromOne =
      1.0F - GetShapePart(0).GetFirstShapePathTDistanceFromClosestBoundary();

  const auto minBrightness       = 2.0F / static_cast<float>(GetTotalNumShapePaths());
  static constexpr auto EXPONENT = 25.0F;
  return STD20::lerp(1.0F, minBrightness, std::pow(distanceFromOne, EXPONENT));
}

auto Shape::Update() noexcept -> void
{
  std::for_each(
      begin(m_shapeParts), end(m_shapeParts), [](ShapePart& shapePart) { shapePart.Update(); });

  m_chromaChangeOnOffTimer.Increment();
  LogInfo("Incremented chroma");
}

auto Shape::DoRandomChanges() noexcept -> void
{
  static constexpr auto PROB_USE_EVEN_PART_NUMS_FOR_DIRECTION = 0.5F;
  const auto useEvenPartNumsForDirection =
      m_goomRand.ProbabilityOf(PROB_USE_EVEN_PART_NUMS_FOR_DIRECTION);

  if (static constexpr auto PROB_CHANGE_CHROMA_STATE = 0.01F;
      m_goomRand.ProbabilityOf(PROB_CHANGE_CHROMA_STATE))
  {
    m_chromaChangeOnOffTimer.TryToChangeState();
  }

  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [&useEvenPartNumsForDirection](ShapePart& shapePart)
                {
                  shapePart.UseEvenShapePartNumsForDirection(useEvenPartNumsForDirection);
                  shapePart.DoRandomChanges();
                });
}

auto Shape::SetFixedShapeNumSteps() noexcept -> void
{
  m_fixedTMinMaxLerp   = ShapePart::GetNewRandomMinMaxLerpT(m_goomRand, m_fixedTMinMaxLerp);
  const auto positionT = GetFirstShapePathPositionT();

  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [this, &positionT](ShapePart& shapePart)
                {
                  shapePart.UseFixedShapePathsNumSteps(m_fixedTMinMaxLerp);
                  shapePart.ResetTs(positionT);
                });
}

auto Shape::SetRandomShapeNumSteps() noexcept -> void
{
  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [](ShapePart& shapePart) { shapePart.UseRandomShapePathsNumSteps(); });
}

auto Shape::GetTotalNumShapePaths() const noexcept -> uint32_t
{
  auto total = 0U;

  const auto numShapeParts = GetNumShapeParts();
  for (auto i = 0U; i < numShapeParts; ++i)
  {
    const auto numShapePaths = m_shapeParts.at(i).GetNumShapePaths();
    for (auto j = 0U; j < numShapePaths; ++j)
    {
      ++total;
    }
  }

  return total;
}

inline auto Shape::StartChromaChangeOnOffTimer() noexcept -> void
{
  m_chromaChangeOnOffTimer.SetActions([this]() { return SetIncreasedChromaFactor(); },
                                      [this]() { return SetDecreasedChromaFactor(); });
  m_chromaChangeOnOffTimer.StartOnTimer();
}

inline auto Shape::SetIncreasedChromaFactor() noexcept -> bool
{
  if (static constexpr auto PROB_INCREASE_CHROMA_FACTOR = 0.9F;
      not m_goomRand.ProbabilityOf(PROB_INCREASE_CHROMA_FACTOR))
  {
    LogInfo("SetIncreasedChromaFactor - return false");
    return false;
  }
  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [](ShapePart& shapePart)
                { shapePart.SetChromaFactor(ColorAdjustment::INCREASED_CHROMA_FACTOR); });
  LogInfo("SetIncreasedChromaFactor - return true");
  return true;
}

inline auto Shape::SetDecreasedChromaFactor() noexcept -> bool
{
  if (static constexpr auto PROB_DECREASE_CHROMA_FACTOR = 0.2F;
      not m_goomRand.ProbabilityOf(PROB_DECREASE_CHROMA_FACTOR))
  {
    LogInfo("SetDecreasedChromaFactor - return false");
    return false;
  }
  std::for_each(begin(m_shapeParts),
                end(m_shapeParts),
                [](ShapePart& shapePart)
                { shapePart.SetChromaFactor(ColorAdjustment::DECREASED_CHROMA_FACTOR); });
  LogInfo("SetDecreasedChromaFactor - return true");
  return true;
}

} // namespace GOOM::VISUAL_FX::SHAPES
