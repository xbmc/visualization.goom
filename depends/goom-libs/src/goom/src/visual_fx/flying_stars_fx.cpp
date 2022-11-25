#include "flying_stars_fx.h"

//#undef NO_LOGGING

#include "color/color_adjustment.h"
#include "color/color_data/color_map_enums.h"
#include "color/color_maps.h"
#include "color/color_utils.h"
#include "color/random_color_maps.h"
#include "flying_stars/star_drawer.h"
#include "flying_stars/star_types.h"
#include "flying_stars/stars.h"
#include "fx_helper.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "logging.h"
#include "point2d.h"
#include "spimpl.h"
#include "utils/graphics/image_bitmaps.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"

#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX
{

using COLOR::ColorAdjustment;
using COLOR::GetLightenedColor;
using COLOR::IColorMap;
using COLOR::RandomColorMaps;
using COLOR::COLOR_DATA::ColorMapName;
using DRAW::MultiplePixels;
using FLYING_STARS::IStarType;
using FLYING_STARS::Star;
using FLYING_STARS::StarDrawer;
using FLYING_STARS::StarTypesContainer;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::GRAPHICS::SmallImageBitmaps;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::Weights;

static constexpr auto COLOR_MAP_MODE_ONE_MAP_PER_ANGLE_WEIGHT      = 30.0F;
static constexpr auto COLOR_MAP_MODE_ONE_MAP_FOR_ALL_ANGLES_WEIGHT = 10.0F;
static constexpr auto COLOR_MAP_MODE_MEGA_RANDOM_WEIGHT            = 01.0F;

static constexpr auto COLOR_MODE_MIX_COLORS_WEIGHT         = 30.0F;
static constexpr auto COLOR_MODE_REVERSE_MIX_COLORS_WEIGHT = 15.0F;
static constexpr auto COLOR_MODE_SIMILAR_LOW_COLORS_WEIGHT = 10.0F;
static constexpr auto COLOR_MODE_SINE_MIX_COLORS_WEIGHT    = 05.0F;

static const inline auto DEFAULT_COLOR_MAP_TYPES = RandomColorMaps::ALL_COLOR_MAP_TYPES;

class FlyingStarsFx::FlyingStarsImpl
{
public:
  FlyingStarsImpl(const FxHelper& fxHelper, const SmallImageBitmaps& smallBitmaps);

  [[nodiscard]] auto GetCurrentStarTypeColorMapsNames() const noexcept -> std::vector<std::string>;
  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void;
  auto SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void;

  auto UpdateBuffers() noexcept -> void;

private:
  const PluginInfo& m_goomInfo;
  const IGoomRand& m_goomRand;
  uint32_t m_counter                  = 0;
  static constexpr uint32_t MAX_COUNT = 100;
  StarDrawer m_starDrawer;

  static constexpr auto GAMMA = 1.0F / 2.0F;
  const ColorAdjustment m_colorAdjust{GAMMA, ColorAdjustment::INCREASED_CHROMA_FACTOR};
  [[nodiscard]] auto GetColorCorrection(float brightness, const Pixel& color) const noexcept
      -> Pixel;

  enum class ColorMode
  {
    MIX_COLORS,
    REVERSE_MIX_COLORS,
    SIMILAR_LOW_COLORS,
    SINE_MIX_COLORS,
    _num // unused, and marks the enum end
  };
  const Weights<ColorMode> m_colorModeWeights;
  ColorMode m_colorMode = m_colorModeWeights.GetRandomWeighted();
  auto ChangeColorMode() noexcept -> void;
  [[nodiscard]] auto GetMixedColors(float brightness, const Star& star, float t) const noexcept
      -> MultiplePixels;
  [[nodiscard]] auto GetFinalMixedColors(float brightness,
                                         const Star::ColorSet& starColorSet,
                                         float t) const noexcept -> MultiplePixels;

  StarTypesContainer m_starTypesContainer{m_goomInfo, m_goomRand};

  static constexpr uint32_t MAX_TOTAL_NUM_ACTIVE_STARS = 1024;
  static constexpr uint32_t MIN_TOTAL_NUM_ACTIVE_STARS = 100;
  std::vector<Star> m_activeStars{};

  auto CheckForStarEvents() noexcept -> void;
  auto SoundEventOccurred() noexcept -> void;
  auto ChangeColorMapMode() noexcept -> void;

  auto DrawStars() noexcept -> void;
  [[nodiscard]] auto IsStarDead(const Star& star) const noexcept -> bool;
  auto RemoveDeadStars() noexcept -> void;

  static constexpr uint32_t MIN_NUM_STAR_CLUSTERS = 0;
  static constexpr uint32_t MAX_NUM_STAR_CLUSTERS = 3;
  static constexpr auto MAX_STAR_CLUSTER_WIDTH    = 320.0F;
  static constexpr auto MAX_STAR_CLUSTER_HEIGHT   = 200.0F;
  // Why 320,200 ? Because the FX was developed on 320x200.
  static constexpr auto MIN_STAR_CLUSTER_HEIGHT = 50.0F;
  const float m_heightRatio =
      static_cast<float>(m_goomInfo.GetScreenHeight()) / MAX_STAR_CLUSTER_HEIGHT;
  auto AddStarClusters() -> void;
  auto AddStarCluster(const IStarType& starType, uint32_t totalNumActiveStars) noexcept -> void;
  [[nodiscard]] auto GetMaxStarsInACluster() const noexcept -> uint32_t;
  auto AddStar(const IStarType& starType, const IStarType::SetupParams& setupParams) noexcept
      -> void;
  [[nodiscard]] auto GetSetupParams(const IStarType& starType) const noexcept
      -> IStarType::SetupParams;
  [[nodiscard]] auto GetNewStarParams(float starPathAngle,
                                      const IStarType::SetupParams& setupParams) const noexcept
      -> Star::Params;

  enum class ColorMapMode
  {
    ONE_MAP_PER_ANGLE,
    ONE_MAP_FOR_ALL_ANGLES,
    ALL_MAPS_RANDOM,
    _num // unused, and marks the enum end
  };
  const Weights<ColorMapMode> m_colorMapModeWeights;
  ColorMapMode m_currentColorMapMode = m_colorMapModeWeights.GetRandomWeighted();

  auto ChangeMapsAndModes() -> void;
  [[nodiscard]] auto GetMainColorMapName(const IStarType& starType) const noexcept -> ColorMapName;
  [[nodiscard]] auto GetLowColorMapName(const IStarType& starType) const noexcept -> ColorMapName;
  [[nodiscard]] auto GetColorMapsSet(const IStarType& starType) const noexcept
      -> Star::ColorMapsSet;
};

FlyingStarsFx::FlyingStarsFx(const FxHelper& fxHelper,
                             const SmallImageBitmaps& smallBitmaps) noexcept
  : m_pimpl{spimpl::make_unique_impl<FlyingStarsImpl>(fxHelper, smallBitmaps)}
{
}

auto FlyingStarsFx::GetFxName() const noexcept -> std::string
{
  return "Flying Stars FX";
}

auto FlyingStarsFx::GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>
{
  return m_pimpl->GetCurrentStarTypeColorMapsNames();
}

auto FlyingStarsFx::SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept
    -> void
{
  m_pimpl->SetWeightedColorMaps(weightedColorMaps);
}

auto FlyingStarsFx::SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void
{
  m_pimpl->SetZoomMidpoint(zoomMidpoint);
}

auto FlyingStarsFx::Start() noexcept -> void
{
  // nothing to be done
}

auto FlyingStarsFx::Finish() noexcept -> void
{
  // nothing to be done
}

auto FlyingStarsFx::Resume() noexcept -> void
{
  // nothing to be done
}

auto FlyingStarsFx::Suspend() noexcept -> void
{
  // nothing to be done
}

auto FlyingStarsFx::ApplyMultiple() noexcept -> void
{
  m_pimpl->UpdateBuffers();
}

FlyingStarsFx::FlyingStarsImpl::FlyingStarsImpl(const FxHelper& fxHelper,
                                                const SmallImageBitmaps& smallBitmaps)
  : m_goomInfo{fxHelper.GetGoomInfo()},
    m_goomRand{fxHelper.GetGoomRand()},
    m_starDrawer{fxHelper.GetDraw(), m_goomRand, smallBitmaps,
                 [this](float brightness, const Star& star, float t) {
                   return GetMixedColors(brightness, star, t); }},
    m_colorModeWeights{
        m_goomRand,
        {
            { ColorMode::MIX_COLORS,         COLOR_MODE_MIX_COLORS_WEIGHT },
            { ColorMode::REVERSE_MIX_COLORS, COLOR_MODE_REVERSE_MIX_COLORS_WEIGHT },
            { ColorMode::SIMILAR_LOW_COLORS, COLOR_MODE_SIMILAR_LOW_COLORS_WEIGHT },
            { ColorMode::SINE_MIX_COLORS,    COLOR_MODE_SINE_MIX_COLORS_WEIGHT },
        }
    },
    m_colorMapModeWeights{
        m_goomRand,
        {
            { ColorMapMode::ONE_MAP_PER_ANGLE,      COLOR_MAP_MODE_ONE_MAP_PER_ANGLE_WEIGHT },
            { ColorMapMode::ONE_MAP_FOR_ALL_ANGLES, COLOR_MAP_MODE_ONE_MAP_FOR_ALL_ANGLES_WEIGHT },
            { ColorMapMode::ALL_MAPS_RANDOM,        COLOR_MAP_MODE_MEGA_RANDOM_WEIGHT },
        }
    }
{
  m_activeStars.reserve(MAX_TOTAL_NUM_ACTIVE_STARS);
}

inline auto FlyingStarsFx::FlyingStarsImpl::GetCurrentStarTypeColorMapsNames() const noexcept
    -> std::vector<std::string>
{
  return m_starTypesContainer.GetCurrentColorMapsNames();
}

auto FlyingStarsFx::FlyingStarsImpl::SetWeightedColorMaps(
    const WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  //LogInfo("Setting weighted color maps for id {}", weightedColorMaps.id);

  Expects(weightedColorMaps.mainColorMaps != nullptr);
  //LogInfo("Main color maps: {}", weightedColorMaps.mainColorMaps->GetColorMapsName());
  m_starTypesContainer.SetWeightedMainColorMaps(weightedColorMaps.id,
                                                weightedColorMaps.mainColorMaps);

  Expects(weightedColorMaps.lowColorMaps != nullptr);
  //LogInfo("Low color maps: {}", weightedColorMaps.lowColorMaps->GetColorMapsName());
  m_starTypesContainer.SetWeightedLowColorMaps(weightedColorMaps.id,
                                               weightedColorMaps.lowColorMaps);

  ChangeColorMapMode();
}

inline auto FlyingStarsFx::FlyingStarsImpl::SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept
    -> void
{
  m_starTypesContainer.SetZoomMidpoint(zoomMidpoint);
}

inline auto FlyingStarsFx::FlyingStarsImpl::UpdateBuffers() noexcept -> void
{
  ++m_counter;

  CheckForStarEvents();
  DrawStars();
  RemoveDeadStars();
}

auto FlyingStarsFx::FlyingStarsImpl::CheckForStarEvents() noexcept -> void
{
  if (not m_activeStars.empty() and (m_goomInfo.GetSoundEvents().GetTimeSinceLastGoom() >= 1))
  {
    return;
  }

  SoundEventOccurred();

  if (static constexpr auto PROB_CHANGE_MAPS_AND_MODES = 1.0F / 20.0F;
      m_goomRand.ProbabilityOf(PROB_CHANGE_MAPS_AND_MODES))
  {
    ChangeMapsAndModes();
  }
  else if (m_counter > MAX_COUNT)
  {
    m_counter = 0;
    ChangeMapsAndModes();
  }
}

inline auto FlyingStarsFx::FlyingStarsImpl::ChangeMapsAndModes() -> void
{
  ChangeColorMode();
  ChangeColorMapMode();
  m_starDrawer.ChangeDrawMode();
}

auto FlyingStarsFx::FlyingStarsImpl::DrawStars() noexcept -> void
{
  const auto speedFactor = m_goomRand.GetRandInRange(0.1F, 10.0F);

  for (auto& star : m_activeStars)
  {
    star.Update();

    if (star.IsTooOld())
    {
      continue;
    }

    m_starDrawer.DrawStar(star, speedFactor);
  }
}

inline auto FlyingStarsFx::FlyingStarsImpl::RemoveDeadStars() noexcept -> void
{
  const auto isDead = [&](const Star& star) { return IsStarDead(star); };
#if __cplusplus <= 201703L
  m_activeStars.erase(std::remove_if(begin(m_activeStars), end(m_activeStars), isDead),
                      end(m_activeStars));
#else
  const auto numRemoved = std::erase_if(m_activeStars, isDead);
#endif
}

auto FlyingStarsFx::FlyingStarsImpl::IsStarDead(const Star& star) const noexcept -> bool
{
  static constexpr auto DEAD_MARGIN = 64;

  if ((star.GetStartPos().x < -DEAD_MARGIN) ||
      (star.GetStartPos().x > static_cast<float>(m_goomInfo.GetScreenWidth() + DEAD_MARGIN)))
  {
    return true;
  }
  if ((star.GetStartPos().y < -DEAD_MARGIN) ||
      (star.GetStartPos().y > static_cast<float>(m_goomInfo.GetScreenHeight() + DEAD_MARGIN)))
  {
    return true;
  }

  return star.IsTooOld();
}

/**
 * Ajoute de nouvelles particules au moment d'un evenement sonore.
 */
inline auto FlyingStarsFx::FlyingStarsImpl::SoundEventOccurred() noexcept -> void
{
  ChangeColorMapMode();
  AddStarClusters();
}

auto FlyingStarsFx::FlyingStarsImpl::AddStarClusters() -> void
{
  const auto numStarClusters = m_goomRand.GetRandInRange(MIN_NUM_STAR_CLUSTERS, 2U);
  const auto totalNumActiveStars =
      m_goomRand.GetRandInRange(MIN_TOTAL_NUM_ACTIVE_STARS, MAX_TOTAL_NUM_ACTIVE_STARS + 1);

  for (auto i = 0U; i < numStarClusters; ++i)
  {
    auto& starType = *m_starTypesContainer.GetRandomStarType();

    starType.UpdateWindAndGravity();
    starType.UpdateFixedColorMapNames();

    AddStarCluster(starType, totalNumActiveStars);
  }
}

inline auto FlyingStarsFx::FlyingStarsImpl::ChangeColorMode() noexcept -> void
{
  m_colorMode = m_colorModeWeights.GetRandomWeighted();
}

inline auto FlyingStarsFx::FlyingStarsImpl::ChangeColorMapMode() noexcept -> void
{
  m_currentColorMapMode = m_colorMapModeWeights.GetRandomWeighted();
}

auto FlyingStarsFx::FlyingStarsImpl::GetColorMapsSet(const IStarType& starType) const noexcept
    -> Star::ColorMapsSet
{
  if (static constexpr auto PROB_RANDOM_COLOR_MAPS = 0.5F;
      m_goomRand.ProbabilityOf(PROB_RANDOM_COLOR_MAPS))
  {
    return {
        starType.GetWeightedMainColorMaps().GetRandomColorMapPtr(DEFAULT_COLOR_MAP_TYPES),
        starType.GetWeightedLowColorMaps().GetRandomColorMapPtr(DEFAULT_COLOR_MAP_TYPES),
        starType.GetWeightedMainColorMaps().GetRandomColorMapPtr(DEFAULT_COLOR_MAP_TYPES),
        starType.GetWeightedLowColorMaps().GetRandomColorMapPtr(DEFAULT_COLOR_MAP_TYPES),
    };
  }

  return {
      starType.GetWeightedMainColorMaps().GetRandomColorMapPtr(GetMainColorMapName(starType),
                                                               DEFAULT_COLOR_MAP_TYPES),
      starType.GetWeightedLowColorMaps().GetRandomColorMapPtr(GetLowColorMapName(starType),
                                                              DEFAULT_COLOR_MAP_TYPES),
      starType.GetWeightedMainColorMaps().GetRandomColorMapPtr(GetMainColorMapName(starType),
                                                               DEFAULT_COLOR_MAP_TYPES),
      starType.GetWeightedLowColorMaps().GetRandomColorMapPtr(GetLowColorMapName(starType),
                                                              DEFAULT_COLOR_MAP_TYPES),
  };
}

inline auto FlyingStarsFx::FlyingStarsImpl::GetMainColorMapName(
    const IStarType& starType) const noexcept -> ColorMapName
{
  switch (m_currentColorMapMode)
  {
    case ColorMapMode::ONE_MAP_PER_ANGLE:
      return starType.GetWeightedMainColorMaps().GetRandomColorMapName();
    case ColorMapMode::ONE_MAP_FOR_ALL_ANGLES:
      return starType.GetFixedMainColorMapName();
    case ColorMapMode::ALL_MAPS_RANDOM:
      return ColorMapName::_NULL;
    default:
      FailFast();
      return ColorMapName::_NULL;
  }
}

inline auto FlyingStarsFx::FlyingStarsImpl::GetLowColorMapName(
    const IStarType& starType) const noexcept -> ColorMapName
{
  switch (m_currentColorMapMode)
  {
    case ColorMapMode::ONE_MAP_PER_ANGLE:
      return starType.GetWeightedLowColorMaps().GetRandomColorMapName();
    case ColorMapMode::ONE_MAP_FOR_ALL_ANGLES:
      return starType.GetFixedLowColorMapName();
    case ColorMapMode::ALL_MAPS_RANDOM:
      return ColorMapName::_NULL;
    default:
      FailFast();
      return ColorMapName::_NULL;
  }
}

auto FlyingStarsFx::FlyingStarsImpl::GetMixedColors(const float brightness,
                                                    const Star& star,
                                                    const float t) const noexcept -> MultiplePixels
{
  Star::ColorSet starColorSet;

  switch (m_colorMode)
  {
    case ColorMode::SINE_MIX_COLORS:
      starColorSet = star.GetSineMixColorSet();
      break;
    case ColorMode::MIX_COLORS:
      starColorSet = star.GetColorSet(t);
      break;
    case ColorMode::SIMILAR_LOW_COLORS:
      starColorSet = star.GetSimilarLowColorSet(t);
      break;
    case ColorMode::REVERSE_MIX_COLORS:
      starColorSet = star.GetReversedMixColorSet(t);
      break;
    default:
      FailFast();
  }

  return GetFinalMixedColors(brightness, starColorSet, t);
}

inline auto FlyingStarsFx::FlyingStarsImpl::GetFinalMixedColors(const float brightness,
                                                                const Star::ColorSet& starColorSet,
                                                                const float t) const noexcept
    -> MultiplePixels
{
  static constexpr auto MIN_MIX = 0.2F;
  static constexpr auto MAX_MIX = 0.8F;
  const auto tMix               = STD20::lerp(MIN_MIX, MAX_MIX, t);
  const auto mixedMainColor     = GetColorCorrection(
      brightness,
      IColorMap::GetColorMix(starColorSet.mainColor, starColorSet.dominantMainColor, tMix));
  const auto mixedLowColor = GetLightenedColor(
      IColorMap::GetColorMix(starColorSet.lowColor, starColorSet.dominantLowColor, tMix), 10.0F);
  const auto remixedLowColor =
      m_colorMode == ColorMode::SIMILAR_LOW_COLORS
          ? mixedLowColor
          : GetColorCorrection(brightness,
                               IColorMap::GetColorMix(mixedMainColor, mixedLowColor, 0.4F));

  return {mixedMainColor, remixedLowColor};
}

inline auto FlyingStarsFx::FlyingStarsImpl::GetColorCorrection(const float brightness,
                                                               const Pixel& color) const noexcept
    -> Pixel
{
  return m_colorAdjust.GetAdjustment(brightness, color);
}

auto FlyingStarsFx::FlyingStarsImpl::AddStarCluster(const IStarType& starType,
                                                    const uint32_t totalNumActiveStars) noexcept
    -> void
{
  const auto starSetupParams    = GetSetupParams(starType);
  const auto maxStarsInACluster = GetMaxStarsInACluster();

  for (auto i = 0U; i < maxStarsInACluster; ++i)
  {
    if (m_activeStars.size() >= totalNumActiveStars)
    {
      break;
    }
    AddStar(starType, starSetupParams);
  }
}

inline auto FlyingStarsFx::FlyingStarsImpl::AddStar(
    const IStarType& starType, const IStarType::SetupParams& setupParams) noexcept -> void
{
  // LogInfo("startPos = {}, {}", setupParams.startPos.x, setupParams.startPos.y);
  const auto newStarPathAngle = starType.GetRandomizedStarPathAngle(setupParams.startPos);

  auto& newStar = m_activeStars.emplace_back(GetNewStarParams(newStarPathAngle, setupParams));

  newStar.SetColorMapsSet(GetColorMapsSet(starType));
}

auto FlyingStarsFx::FlyingStarsImpl::GetNewStarParams(
    const float starPathAngle, const IStarType::SetupParams& setupParams) const noexcept
    -> Star::Params
{
  const auto starPathLength =
      setupParams.nominalPathLength * m_goomRand.GetRandInRange(0.01F, 2.0F);
  static constexpr auto LENGTH_OFFSET = -0.2F;

  const auto initialPosition     = setupParams.startPos.ToFlt();
  const auto initialVelocity     = Vec2dFlt{starPathLength * std::cos(starPathAngle),
                                        LENGTH_OFFSET + (starPathLength * std::sin(starPathAngle))};
  const auto initialAcceleration = Vec2dFlt{setupParams.sideWind, setupParams.gravity};
  const auto initialAge =
      m_goomRand.GetRandInRange(Star::MIN_INITIAL_AGE, Star::HALF_MAX_INITIAL_AGE);
  const auto initialVAge = std::max(Star::MIN_INITIAL_AGE, setupParams.vage);
  const auto maxAge      = setupParams.maxStarAge;

  return {initialPosition, initialVelocity, initialAcceleration, initialAge, initialVAge, maxAge};
}

inline auto FlyingStarsFx::FlyingStarsImpl::GetMaxStarsInACluster() const noexcept -> uint32_t
{
  const auto maxStarsInACluster = static_cast<uint32_t>(
      m_heightRatio * (100.0F + ((m_goomInfo.GetSoundEvents().GetGoomPower() + 1.0F) *
                                 m_goomRand.GetRandInRange(0.0F, 150.0F))));

  if (m_goomInfo.GetSoundEvents().GetTimeSinceLastBigGoom() < 1)
  {
    return 2 * maxStarsInACluster;
  }

  return maxStarsInACluster;
}

auto FlyingStarsFx::FlyingStarsImpl::GetSetupParams(const IStarType& starType) const noexcept
    -> IStarType::SetupParams
{
  const auto defaultPathLength =
      (1.0F + m_goomInfo.GetSoundEvents().GetGoomPower()) *
      (m_goomRand.GetRandInRange(MIN_STAR_CLUSTER_HEIGHT, MAX_STAR_CLUSTER_HEIGHT) /
       MAX_STAR_CLUSTER_WIDTH);

  auto setupParams = starType.GetRandomizedSetupParams(defaultPathLength);

  setupParams.nominalPathLength *= m_heightRatio;
  if (m_goomInfo.GetSoundEvents().GetTimeSinceLastBigGoom() < 1)
  {
    static constexpr auto LENGTH_FACTOR = 1.5F;
    setupParams.nominalPathLength *= LENGTH_FACTOR;
  }

  return setupParams;
}

} // namespace GOOM::VISUAL_FX
