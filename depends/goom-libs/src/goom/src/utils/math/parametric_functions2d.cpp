#include "parametric_functions2d.h"

#include "goom_config.h"
#include "misc.h"
#include "point2d.h"

#include <cmath>

namespace GOOM::UTILS::MATH
{

auto IParametricFunction2d::GetPointData(const float t) const noexcept -> PointData
{
  return {GetPoint(t), HALF_PI};
}

CircleFunction::CircleFunction(const Vec2dFlt& centrePos,
                               const float radius,
                               const AngleParams& angleParams,
                               const Direction direction) noexcept
  : m_centrePos{centrePos}, m_radius{radius}, m_angleParams{angleParams}, m_direction{direction}
{
}

auto CircleFunction::GetPointAtAngle(float angle) const noexcept -> Point2dFlt
{
  if (m_direction == Direction::CLOCKWISE)
  {
    angle = -angle;
  }

  return Point2dFlt{m_radius * std::cos(angle), -m_radius * std::sin(angle)} + m_centrePos;
}

SpiralFunction::SpiralFunction(const Vec2dFlt& centrePos,
                               const uint32_t numTurns,
                               const Direction direction,
                               const float minRadius,
                               const float maxRadius) noexcept
  : m_centrePos{centrePos},
    m_minRadius{minRadius},
    m_maxRadius{maxRadius},
    m_angleFactor{direction == Direction::COUNTER_CLOCKWISE
                      ? -(static_cast<float>(numTurns) * TWO_PI)
                      : +(static_cast<float>(numTurns) * TWO_PI)}
{
}

LissajousFunction::LissajousFunction(const Vec2dFlt& centrePos,
                                     const AngleParams& angleParams,
                                     const Params& params) noexcept
  : m_centrePos{centrePos}, m_angleParams{angleParams}, m_params{params}
{
}

auto LissajousFunction::GetPointAtAngle(const float angle) const noexcept -> Point2dFlt
{
  return Point2dFlt{+m_params.a * std::cos(m_params.kX * angle),
                    -m_params.b * std::sin(m_params.kY * angle)} +
         m_centrePos;
}

HypotrochoidFunction::HypotrochoidFunction(const Vec2dFlt& centrePos,
                                           const AngleParams& angleParams,
                                           const Params& params) noexcept
  : m_centrePos{centrePos},
    m_angleParams{angleParams},
    m_params{params},
    m_rDiff{m_params.bigR - m_params.smallR},
    m_numCusps{GetNumCusps(m_params.bigR, m_params.smallR)}
{
  Expects(params.bigR > 0.0F);
  Expects(params.smallR > 0.0F);
  Expects(params.amplitude > 0.0F);
  Expects(angleParams.startAngleInRadians <= angleParams.endAngleInRadians);
}

auto HypotrochoidFunction::GetNumCusps(const float bigR, const float smallR) noexcept -> float
{
  const auto intBigR   = static_cast<int32_t>(bigR + SMALL_FLOAT);
  const auto intSmallR = static_cast<int32_t>(smallR + SMALL_FLOAT);

  if ((0 == intBigR) || (0 == intSmallR))
  {
    return 1.0F;
  }

  return static_cast<float>(Lcm(intSmallR, intBigR) / static_cast<int64_t>(intBigR));
}

auto HypotrochoidFunction::GetPointAtAngle(const float angle) const noexcept -> Point2dFlt
{
  const auto angleArg2 = (m_rDiff / m_params.smallR) * angle;

  const auto x = +(m_rDiff * std::cos(angle)) + (m_params.height * std::cos(angleArg2));
  const auto y = -(m_rDiff * std::sin(angle)) + (m_params.height * std::sin(angleArg2));

  return (m_params.amplitude * Point2dFlt{x, y}) + m_centrePos;
}

EpicycloidFunction::EpicycloidFunction(const Vec2dFlt& centrePos,
                                       const AngleParams& angleParams,
                                       const Params& params) noexcept
  : m_centrePos{centrePos},
    m_angleParams{angleParams},
    m_params{params},
    m_numCusps{GetNumCusps(m_params.k)}
{
  Expects(params.k > 0.0F);
  Expects(params.smallR > 0.0F);
  Expects(params.amplitude > 0.0F);
  Expects(angleParams.startAngleInRadians <= angleParams.endAngleInRadians);
}

auto EpicycloidFunction::GetNumCusps([[maybe_unused]] const float k) noexcept -> float
{
  // From 'https://en.wikipedia.org/wiki/Epicycloid'
  if (const RationalNumber frac = FloatToIrreducibleFraction(k); frac.isRational)
  {
    return static_cast<float>(frac.numerator);
  }

  // k is irrational. Curve never closes, so return 'large' number.
  static constexpr auto LARGE_NUM_CUSPS = 20.0F;
  return LARGE_NUM_CUSPS;
}

auto EpicycloidFunction::GetPointAtAngle(const float angle) const noexcept -> Point2dFlt
{
  const auto angleArg2 = (m_params.k + 1.0F) * angle;

  const auto x = +(m_params.smallR * (m_params.k + 1.0F) * std::cos(angle)) -
                 +(m_params.smallR * std::cos(angleArg2));
  const auto y = -(m_params.smallR * (m_params.k + 1.0F) * std::sin(angle)) +
                 +(m_params.smallR * std::sin(angleArg2));

  return (m_params.amplitude * Point2dFlt{x, y}) + m_centrePos;
}

SineFunction::SineFunction(const Point2dFlt& startPos,
                           const Point2dFlt& endPos,
                           const Params& params) noexcept
  : m_startPos{startPos},
    m_endPos{endPos},
    m_params{params},
    m_distance{Distance(m_startPos, m_endPos)},
    m_rotateAngle{std::asin((m_endPos.y - m_startPos.y) / m_distance)}
{
}

auto SineFunction::GetPoint(const float t) const noexcept -> Point2dFlt
{
  const auto y = 100.0F * std::sin(m_params.freq * TWO_PI * t);
  const auto x = m_distance * t;

  auto newPoint = Point2dFlt{x, y};
  newPoint.Rotate(m_rotateAngle);

  return (Point2dFlt{newPoint.x, (m_params.amplitude * newPoint.y)} + Vec2dFlt{m_startPos});
}

OscillatingFunction::OscillatingFunction(const Point2dFlt& startPos,
                                         const Point2dFlt& endPos,
                                         const Params& params) noexcept
  : m_params{params}, m_startPos{GetAdjustedStartPos(startPos)}, m_endPos{endPos}
{
}

auto OscillatingFunction::GetPoint(const float t) const noexcept -> Point2dFlt
{
  const auto linearPoint = lerp(m_startPos, m_endPos, t);
  return GetOscillatingPoint(linearPoint, t);
}

inline auto OscillatingFunction::GetOscillatingPoint(const Point2dFlt& linearPoint,
                                                     const float t) const noexcept -> Point2dFlt
{
  return linearPoint + GetOscillatingOffset(t);
}

inline auto OscillatingFunction::GetOscillatingOffset(const float t) const noexcept -> Vec2dFlt
{
  if (not m_allowOscillatingPath)
  {
    return {0, 0};
  }

  return {
      m_params.oscillatingAmplitude * std::cos(m_params.xOscillatingFreq * t * TWO_PI),
      m_params.oscillatingAmplitude * std::sin(m_params.yOscillatingFreq * t * TWO_PI),
  };
}

auto OscillatingFunction::GetAdjustedStartPos(const Point2dFlt& startPos) const noexcept
    -> Point2dFlt
{
  return startPos - GetOscillatingOffset(0.0F);
}

} // namespace GOOM::UTILS::MATH
