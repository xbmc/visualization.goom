#include "circle_params_builder.h"

#include "utils/math/misc.h"

namespace GOOM::VISUAL_FX::CIRCLES
{

using UTILS::MATH::HALF;
using UTILS::MATH::U_FIFTH;

CircleParamsBuilder::CircleParamsBuilder(const uint32_t numCircles,
                                         const FxHelper& fxHelper) noexcept
  : m_numCircles{numCircles}, m_fxHelper{fxHelper}
{
}

auto CircleParamsBuilder::GetCircleParamsTargetsOnly(
    const std::vector<Circle::Params>& circleParams) const noexcept -> std::vector<Circle::Params>
{
  auto newCircleParams = circleParams;

  SetCircleCentreTargets(newCircleParams);

  return newCircleParams;
}

auto CircleParamsBuilder::GetCircleParams() const noexcept -> std::vector<Circle::Params>
{
  auto circleParams = std::vector<Circle::Params>(m_numCircles);

  SetCircleCentreStarts(circleParams);
  SetCircleCentreTargets(circleParams);

  return circleParams;
}

inline auto CircleParamsBuilder::SetCircleCentreStarts(
    std::vector<Circle::Params>& circleParams) const noexcept -> void
{
  const auto mainCircleRadius   = GetMainCircleRadius();
  const auto circleRadii        = GetCircleRadii(mainCircleRadius);
  const auto circleCentreStarts = GetCircleCentreStarts(mainCircleRadius);

  for (auto i = 0U; i < m_numCircles; ++i)
  {
    circleParams[i].toTargetParams.circleRadius   = circleRadii[i];
    circleParams[i].fromTargetParams.circleRadius = circleRadii[i];

    circleParams[i].toTargetParams.circleCentreStart   = circleCentreStarts[i];
    circleParams[i].fromTargetParams.circleCentreStart = circleCentreStarts[i];
  }
}

inline auto CircleParamsBuilder::GetMainCircleRadius() const noexcept -> float
{
  static constexpr auto MIN_RADIUS_MARGIN = 100.0F;
  static constexpr auto MAX_RADIUS_MARGIN = 200.01F;
  const auto radiusMargin =
      m_fxHelper.GetGoomRand().GetRandInRange(MIN_RADIUS_MARGIN, MAX_RADIUS_MARGIN);

  const auto maxRadius = 0.5F * static_cast<float>(std::min(m_screenWidth, m_screenHeight));

  return maxRadius - radiusMargin;
}

auto CircleParamsBuilder::GetCircleRadii(const float mainCircleRadius) const noexcept
    -> std::vector<float>
{
  if (m_circleStartMode == CircleStartModes::SAME_RADIUS)
  {
    return GetSameCircleRadii(mainCircleRadius);
  }
  if (m_circleStartMode == CircleStartModes::REDUCING_RADIUS)
  {
    return GetReducingCircleRadii(mainCircleRadius);
  }
  return GetFourCornersCircleRadii(mainCircleRadius);
}

auto CircleParamsBuilder::GetSameCircleRadii(const float mainCircleRadius) const noexcept
    -> std::vector<float>
{
  auto sameRadii = std::vector<float>(m_numCircles);
  std::fill(begin(sameRadii), end(sameRadii), mainCircleRadius);
  return sameRadii;
}

auto CircleParamsBuilder::GetReducingCircleRadii(const float mainCircleRadius) const noexcept
    -> std::vector<float>
{
  const auto radiusReducer = GetCircleRadiusReducer();

  auto reducingRadii = std::vector<float>(m_numCircles);

  reducingRadii.at(0) = mainCircleRadius;
  for (auto i = 1U; i < m_numCircles; ++i)
  {
    reducingRadii[i] = radiusReducer * reducingRadii[i - 1];
  }

  return reducingRadii;
}

inline auto CircleParamsBuilder::GetCircleRadiusReducer() const noexcept -> float
{
  static constexpr auto MIN_RADIUS_REDUCER = 0.60F;
  static constexpr auto MAX_RADIUS_REDUCER = 1.01F;
  return m_fxHelper.GetGoomRand().GetRandInRange(MIN_RADIUS_REDUCER, MAX_RADIUS_REDUCER);
}

inline auto CircleParamsBuilder::GetFourCornersCircleRadii(
    const float mainCircleRadius) const noexcept -> std::vector<float>
{
  Expects(5 == m_numCircles);

  const auto innerCircleRadius = HALF * mainCircleRadius;

  auto fourCornersRadii = std::vector<float>(m_numCircles);

  fourCornersRadii.at(0) = mainCircleRadius;
  for (auto i = 1U; i < m_numCircles; ++i)
  {
    fourCornersRadii.at(i) = innerCircleRadius;
  }

  return fourCornersRadii;
}

inline auto CircleParamsBuilder::GetCircleCentreStarts(const float mainCircleRadius) const noexcept
    -> std::vector<Point2dInt>
{
  switch (m_circleStartMode)
  {
    case CircleStartModes::SAME_RADIUS:
      return GetAllSameCircleCentreStarts(mainCircleRadius);
    case CircleStartModes::REDUCING_RADIUS:
      return GetReducingRadiusCircleCentreStarts(mainCircleRadius);
    case CircleStartModes::FOUR_CORNERED_IN_MAIN:
      return GetFourCornersCircleCentreStarts(mainCircleRadius);
    default:
      FailFast();
      return {};
  }
}

inline auto CircleParamsBuilder::GetAllSameCircleCentreStarts(
    [[maybe_unused]] const float mainCircleRadius) const noexcept -> std::vector<Point2dInt>
{
  auto circleCentreStarts = std::vector<Point2dInt>(m_numCircles);
  std::fill(begin(circleCentreStarts), end(circleCentreStarts), m_mainCircleCentreStart);
  return circleCentreStarts;
}

inline auto CircleParamsBuilder::GetReducingRadiusCircleCentreStarts(
    [[maybe_unused]] const float mainCircleRadius) const noexcept -> std::vector<Point2dInt>
{
  auto circleCentreStarts = std::vector<Point2dInt>(m_numCircles);
  std::fill(begin(circleCentreStarts), end(circleCentreStarts), m_mainCircleCentreStart);
  return circleCentreStarts;
}

inline auto CircleParamsBuilder::GetFourCornersCircleCentreStarts(
    const float mainCircleRadius) const noexcept -> std::vector<Point2dInt>
{
  Expects(5 == m_numCircles);

  const auto innerCircleRadius = HALF * mainCircleRadius;
  const auto offset =
      static_cast<int32_t>(m_fxHelper.GetGoomRand().GetRandInRange(0.5F, 1.0F) * innerCircleRadius);

  auto circleCentreStarts = std::vector<Point2dInt>(m_numCircles);

  circleCentreStarts.at(0) = m_mainCircleCentreStart;
  circleCentreStarts.at(1) = {m_mainCircleCentreStart.x, m_mainCircleCentreStart.y - offset};
  circleCentreStarts.at(2) = {m_mainCircleCentreStart.x + offset, m_mainCircleCentreStart.y};
  circleCentreStarts.at(3) = {m_mainCircleCentreStart.x, m_mainCircleCentreStart.y + offset};
  circleCentreStarts.at(4) = {m_mainCircleCentreStart.x - offset, m_mainCircleCentreStart.y};

  return circleCentreStarts;
}

inline auto CircleParamsBuilder::SetCircleCentreTargets(
    std::vector<Circle::Params>& circleParams) const noexcept -> void
{
  const auto circleCentreTargets = GetCircleCentreTargets(m_mainCircleCentreTarget);

  for (auto i = 0U; i < m_numCircles; ++i)
  {
    circleParams[i].toTargetParams.circleCentreTarget   = circleCentreTargets.at(i);
    circleParams[i].fromTargetParams.circleCentreTarget = circleCentreTargets.at(i);
  }
}

inline auto CircleParamsBuilder::GetCircleCentreTargets(const Point2dInt& target) const noexcept
    -> std::vector<Point2dInt>
{
  if (m_circleTargetMode == CircleTargetModes::SIMILAR_TARGETS)
  {
    return GetSimilarCircleCentreTargets(target);
  }
  return GetFourCornersCircleCentreTargets(target);
}

inline auto CircleParamsBuilder::GetSimilarCircleCentreTargets(
    const Point2dInt& target) const noexcept -> std::vector<Point2dInt>
{
  auto circleCentreTargets = std::vector<Point2dInt>(m_numCircles);

  static constexpr auto MIN_OFFSET = 0U;
  const auto maxOffset             = U_FIFTH * std::min(m_screenWidth, m_screenHeight);

  for (auto& circleCentre : circleCentreTargets)
  {
    circleCentre =
        target + Vec2dInt{m_fxHelper.GetGoomRand().GetRandInRange(MIN_OFFSET, maxOffset),
                          m_fxHelper.GetGoomRand().GetRandInRange(MIN_OFFSET, maxOffset)};
  }

  return circleCentreTargets;
}

inline auto CircleParamsBuilder::GetFourCornersCircleCentreTargets(
    const Point2dInt& target) const noexcept -> std::vector<Point2dInt>
{
  Expects(5 == m_numCircles);

  auto circleCentreTargets = std::vector<Point2dInt>(m_numCircles);

  static constexpr auto MIN_T = 0.05F;
  static constexpr auto MAX_T = 0.95F;
  const auto t                = m_fxHelper.GetGoomRand().GetRandInRange(MIN_T, MAX_T);

  circleCentreTargets.at(0) = target;
  circleCentreTargets.at(1) = lerp(m_topLeftCorner, circleCentreTargets.at(0), t);
  circleCentreTargets.at(2) = lerp(m_topRightCorner, circleCentreTargets.at(0), t);
  circleCentreTargets.at(3) = lerp(m_bottomLeftCorner, circleCentreTargets.at(0), t);
  circleCentreTargets.at(4) = lerp(m_bottomRightCorner, circleCentreTargets.at(0), t);

  return circleCentreTargets;
}

} // namespace GOOM::VISUAL_FX::CIRCLES
