#include "circles_fx.h"

//#undef NO_LOGGING

#include "fx_helper.h"
#include "logging.h"
#include "spimpl.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/misc.h"
#include "utils/math/paths.h"
#include "utils/timer.h"
#include "visual_fx/circles/circle_params_builder.h"
#include "visual_fx/circles/circles.h"

#include <memory>
#include <vector>

namespace GOOM::VISUAL_FX
{

using CIRCLES::Circle;
using CIRCLES::CircleParamsBuilder;
using CIRCLES::Circles;
using CIRCLES::DotPaths;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::Timer;
using UTILS::GRAPHICS::SmallImageBitmaps;
using UTILS::MATH::OscillatingFunction;
using UTILS::MATH::Weights;

class CirclesFx::CirclesFxImpl
{
public:
  CirclesFxImpl(const FxHelper& fxHelper, const SmallImageBitmaps& smallBitmaps) noexcept;

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>;
  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void;

  auto SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void;

  auto Start() noexcept -> void;
  auto ApplyMultiple() noexcept -> void;

private:
  const FxHelper& m_fxHelper;
  const SmallImageBitmaps& m_smallBitmaps;
  const Point2dInt m_screenMidPoint = MidpointFromOrigin(
      {m_fxHelper.GetGoomInfo().GetScreenWidth(), m_fxHelper.GetGoomInfo().GetScreenHeight()});

  static constexpr uint32_t NUM_CIRCLES = 5;
  const Weights<CircleParamsBuilder::CircleStartModes> m_weightedCircleStartModes;
  const Weights<CircleParamsBuilder::CircleTargetModes> m_weightedCircleTargetModes;
  CircleParamsBuilder m_circleParamsBuilder{NUM_CIRCLES, m_fxHelper};
  std::vector<Circle::Params> m_circleParams{m_circleParamsBuilder.GetCircleParams()};
  std::unique_ptr<Circles> m_circles{MakeCircles()};
  [[nodiscard]] auto MakeCircles() const noexcept -> std::unique_ptr<Circles>;
  [[nodiscard]] auto GetBrightnessFactors() const noexcept -> std::vector<float>;

  auto DrawCircles() noexcept -> void;
  auto IncrementTs() noexcept -> void;
  uint64_t m_updateNum = 0;
  auto UpdateStates() noexcept -> void;
  auto UpdateCirclePathParams() noexcept -> void;
  [[nodiscard]] auto GetPathParams() const noexcept -> std::vector<OscillatingFunction::Params>;
  [[nodiscard]] auto GetNextCircleCentre(const Point2dInt& zoomMidpoint) const noexcept
      -> Point2dInt;

  bool m_circlesFullReset = false;
  WeightedColorMaps m_lastWeightedColorMaps{};
  auto CheckCirclesFullReset() noexcept -> void;

  static constexpr uint32_t MIN_BLANK_AT_TARGET_TIME = 1;
  static constexpr uint32_t MAX_BLANK_AT_TARGET_TIME = 5;
  uint32_t m_blankAtTargetTime                       = m_fxHelper.GetGoomRand().GetRandInRange(
      MIN_BLANK_AT_TARGET_TIME, MAX_BLANK_AT_TARGET_TIME + 1);
  Timer m_blankAtTargetTimer{m_blankAtTargetTime, true};

  static constexpr uint32_t MIN_PAUSE_AT_START_TIME = 0;
  static constexpr uint32_t MAX_PAUSE_AT_START_TIME = 0;
  uint32_t m_pauseAtStartTime =
      m_fxHelper.GetGoomRand().GetRandInRange(MIN_PAUSE_AT_START_TIME, MAX_PAUSE_AT_START_TIME + 1);
  Timer m_pauseAtStartTimer{m_pauseAtStartTime, true};
};

CirclesFx::CirclesFx(const FxHelper& fxHelper, const SmallImageBitmaps& smallBitmaps) noexcept
  : m_pimpl{spimpl::make_unique_impl<CirclesFxImpl>(fxHelper, smallBitmaps)}
{
}

auto CirclesFx::GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>
{
  return m_pimpl->GetCurrentColorMapsNames();
}

auto CirclesFx::SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  m_pimpl->SetWeightedColorMaps(weightedColorMaps);
}

auto CirclesFx::SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept -> void
{
  m_pimpl->SetZoomMidpoint(zoomMidpoint);
}

auto CirclesFx::Start() noexcept -> void
{
  m_pimpl->Start();
}

auto CirclesFx::Finish() noexcept -> void
{
  // nothing to do
}

auto CirclesFx::GetFxName() const noexcept -> std::string
{
  return "circles";
}

auto CirclesFx::ApplyMultiple() noexcept -> void
{
  m_pimpl->ApplyMultiple();
}

using CircleStartModes  = CircleParamsBuilder::CircleStartModes;
using CircleTargetModes = CircleParamsBuilder::CircleTargetModes;

static constexpr auto CIRCLE_START_SAME_RADIUS_WEIGHT      = 10.0F;
static constexpr auto CIRCLE_START_FOUR_CORNERED_WEIGHT    = 10.0F;
static constexpr auto CIRCLE_START_REDUCING_RADIUS_WEIGHT  = 10.0F;
static constexpr auto CIRCLE_TARGET_SIMILAR_TARGETS_WEIGHT = 10.0F;
static constexpr auto CIRCLE_TARGET_FOUR_CORNERS_WEIGHT    = 10.0F;

CirclesFx::CirclesFxImpl::CirclesFxImpl(const FxHelper& fxHelper,
                                        const SmallImageBitmaps& smallBitmaps) noexcept
  : m_fxHelper{fxHelper}, m_smallBitmaps{smallBitmaps},
    m_weightedCircleStartModes{
        m_fxHelper.GetGoomRand(),
        {
            {CircleStartModes::SAME_RADIUS, CIRCLE_START_SAME_RADIUS_WEIGHT},
            {CircleStartModes::FOUR_CORNERED_IN_MAIN, CIRCLE_START_FOUR_CORNERED_WEIGHT},
            {CircleStartModes::REDUCING_RADIUS, CIRCLE_START_REDUCING_RADIUS_WEIGHT},
        }
    },
    m_weightedCircleTargetModes{
        m_fxHelper.GetGoomRand(),
        {
            {CircleTargetModes::SIMILAR_TARGETS, CIRCLE_TARGET_SIMILAR_TARGETS_WEIGHT},
            {CircleTargetModes::FOUR_CORNERS, CIRCLE_TARGET_FOUR_CORNERS_WEIGHT},
        }
    }
{
}

inline auto CirclesFx::CirclesFxImpl::MakeCircles() const noexcept -> std::unique_ptr<Circles>
{
  auto circles = std::make_unique<Circles>(
      m_fxHelper, m_smallBitmaps, NUM_CIRCLES, GetPathParams(), m_circleParams);

  circles->SetGlobalBrightnessFactors(GetBrightnessFactors());

  return circles;
}

auto CirclesFx::CirclesFxImpl::GetBrightnessFactors() const noexcept -> std::vector<float>
{
  static constexpr auto LARGE_ENOUGH_RADIUS_RATIO = 0.15F;
  const auto mainCircleRadius = m_circleParams.at(0).toTargetParams.circleRadius;

  LogInfo("mainCircleRadius = {}", mainCircleRadius);

  auto brightnessFactors = std::vector<float>(NUM_CIRCLES);
  for (auto i = 0U; i < NUM_CIRCLES; ++i)
  {
    LogInfo("circleRadius[{}] = {}", i, m_circleParams.at(i).toTargetParams.circleRadius);
    const auto radiusFactor = m_circleParams.at(i).toTargetParams.circleRadius / mainCircleRadius;
    LogInfo("radiusFactor[{}] = {}", i, radiusFactor);
    brightnessFactors.at(i) = radiusFactor > LARGE_ENOUGH_RADIUS_RATIO ? 1.0F : 0.1F;
  }

  return brightnessFactors;
}

inline auto CirclesFx::CirclesFxImpl::GetCurrentColorMapsNames() const noexcept
    -> std::vector<std::string>
{
  return {};
}

inline auto CirclesFx::CirclesFxImpl::SetWeightedColorMaps(
    const WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  Expects(weightedColorMaps.mainColorMaps != nullptr);
  Expects(weightedColorMaps.lowColorMaps != nullptr);

  m_circles->SetWeightedColorMaps(weightedColorMaps.mainColorMaps, weightedColorMaps.lowColorMaps);

  m_lastWeightedColorMaps = weightedColorMaps;
}

inline auto CirclesFx::CirclesFxImpl::SetZoomMidpoint(const Point2dInt& zoomMidpoint) noexcept
    -> void
{
  if (zoomMidpoint == m_circleParamsBuilder.GetMainCircleCentreTarget())
  {
    return;
  }

  m_circleParamsBuilder.SetMainCircleStartCentre(GetNextCircleCentre(zoomMidpoint));
  m_circleParamsBuilder.SetMainCircleCentreTarget(zoomMidpoint);

  m_circlesFullReset = true;
}

inline auto CirclesFx::CirclesFxImpl::GetNextCircleCentre(
    const Point2dInt& zoomMidpoint) const noexcept -> Point2dInt
{
  static constexpr auto MIN_LERP = 0.0F;
  static constexpr auto MAX_LERP = 1.0F;
  const auto midLerp             = m_fxHelper.GetGoomRand().GetRandInRange(MIN_LERP, MAX_LERP);
  auto newCircleCentre           = lerp(m_screenMidPoint, zoomMidpoint, midLerp);

  const auto minX = m_fxHelper.GetGoomInfo().GetScreenWidth() / 10;
  const auto maxX = m_fxHelper.GetGoomInfo().GetScreenWidth() - minX;
  const auto minY = m_fxHelper.GetGoomInfo().GetScreenHeight() / 10;
  const auto maxY = m_fxHelper.GetGoomInfo().GetScreenHeight() - minY;
  newCircleCentre.x =
      std::clamp(newCircleCentre.x, static_cast<int32_t>(minX), static_cast<int32_t>(maxX));
  newCircleCentre.y =
      std::clamp(newCircleCentre.y, static_cast<int32_t>(minY), static_cast<int32_t>(maxY));

  return newCircleCentre;
}

inline auto CirclesFx::CirclesFxImpl::Start() noexcept -> void
{
  m_updateNum = 0;

  m_blankAtTargetTimer.SetToFinished();
  m_pauseAtStartTimer.SetToFinished();

  m_circles->Start();
}

inline auto CirclesFx::CirclesFxImpl::ApplyMultiple() noexcept -> void
{
  UpdateStates();
  DrawCircles();
  CheckCirclesFullReset();
}

inline auto CirclesFx::CirclesFxImpl::DrawCircles() noexcept -> void
{
  m_blankAtTargetTimer.Increment();
  if (not m_blankAtTargetTimer.Finished())
  {
    return;
  }

  m_circles->UpdateAndDraw();
  IncrementTs();

  if (m_circles->HasPositionTJustHitEndBoundary())
  {
    m_blankAtTargetTimer.SetTimeLimit(m_blankAtTargetTime);
  }
}

inline auto CirclesFx::CirclesFxImpl::IncrementTs() noexcept -> void
{
  m_pauseAtStartTimer.Increment();
  if (not m_pauseAtStartTimer.Finished())
  {
    return;
  }

  m_circles->IncrementTs();

  if (m_circles->HasPositionTJustHitStartBoundary())
  {
    m_pauseAtStartTimer.SetTimeLimit(m_pauseAtStartTime);
  }
}

inline auto CirclesFx::CirclesFxImpl::UpdateStates() noexcept -> void
{
  ++m_updateNum;

  if (static constexpr auto NUM_UPDATE_SKIPS = 10U; (m_updateNum % NUM_UPDATE_SKIPS) != 0)
  {
    return;
  }

  m_blankAtTargetTime = m_fxHelper.GetGoomRand().GetRandInRange(MIN_BLANK_AT_TARGET_TIME,
                                                                MAX_BLANK_AT_TARGET_TIME + 1);
  m_pauseAtStartTime =
      m_fxHelper.GetGoomRand().GetRandInRange(MIN_PAUSE_AT_START_TIME, MAX_PAUSE_AT_START_TIME + 1);

  m_circleParamsBuilder.SetCircleStartMode(m_weightedCircleStartModes.GetRandomWeighted());
  m_circleParamsBuilder.SetCircleTargetMode(m_weightedCircleTargetModes.GetRandomWeighted());
  m_circlesFullReset = true;

  UpdateCirclePathParams();
}

inline auto CirclesFx::CirclesFxImpl::UpdateCirclePathParams() noexcept -> void
{
  if (m_fxHelper.GetGoomInfo().GetSoundEvents().GetTimeSinceLastGoom() > 0)
  {
    return;
  }

  m_circles->SetPathParams(GetPathParams());
}

inline auto CirclesFx::CirclesFxImpl::GetPathParams() const noexcept
    -> std::vector<OscillatingFunction::Params>
{
  static constexpr auto MIN_PATH_AMPLITUDE = 90.0F;
  static constexpr auto MAX_PATH_AMPLITUDE = 110.0F;
  static constexpr auto MIN_PATH_X_FREQ    = 0.9F;
  static constexpr auto MAX_PATH_X_FREQ    = 2.0F;
  static constexpr auto MIN_PATH_Y_FREQ    = 0.9F;
  static constexpr auto MAX_PATH_Y_FREQ    = 2.0F;

  const auto params = OscillatingFunction::Params{
      m_fxHelper.GetGoomRand().GetRandInRange(MIN_PATH_AMPLITUDE, MAX_PATH_AMPLITUDE),
      m_fxHelper.GetGoomRand().GetRandInRange(MIN_PATH_X_FREQ, MAX_PATH_X_FREQ),
      m_fxHelper.GetGoomRand().GetRandInRange(MIN_PATH_Y_FREQ, MAX_PATH_Y_FREQ),
  };

  auto pathParams = std::vector<OscillatingFunction::Params>(NUM_CIRCLES);
  std::fill(begin(pathParams), end(pathParams), params);

  return pathParams;
}

inline auto CirclesFx::CirclesFxImpl::CheckCirclesFullReset() noexcept -> void
{
  if (not m_circlesFullReset)
  {
    return;
  }
  if (not m_circles->HasPositionTJustHitEndBoundary())
  {
    return;
  }

  Expects(not m_blankAtTargetTimer.Finished());
  Expects(m_circles->HasPositionTJustHitEndBoundary());
  Expects(m_circles->GetCurrentDirection() == DotPaths::Direction::TO_TARGET);

  m_circleParams = m_circleParamsBuilder.GetCircleParams();
  m_circles      = MakeCircles();
  m_circles->ChangeDirection(DotPaths::Direction::FROM_TARGET);
  m_circles->SetWeightedColorMaps(m_lastWeightedColorMaps.mainColorMaps,
                                  m_lastWeightedColorMaps.lowColorMaps);
  m_circlesFullReset = false;

  Ensures(m_circles->GetCurrentDirection() == DotPaths::Direction::FROM_TARGET);
}

} // namespace GOOM::VISUAL_FX
