#pragma once

#include "misc.h"
#include "point2d.h"

#include <cmath>
#include <functional>

namespace GOOM::UTILS::MATH
{

class IParametricFunction2d
{
public:
  IParametricFunction2d() noexcept                                       = default;
  IParametricFunction2d(const IParametricFunction2d&) noexcept           = default;
  IParametricFunction2d(IParametricFunction2d&&) noexcept                = default;
  virtual ~IParametricFunction2d() noexcept                              = default;
  auto operator=(const IParametricFunction2d&) -> IParametricFunction2d& = delete;
  auto operator=(IParametricFunction2d&&) -> IParametricFunction2d&      = delete;

  [[nodiscard]] virtual auto GetPoint(float t) const noexcept -> Point2dFlt = 0;

  struct PointData
  {
    Point2dFlt point;
    float normalAngle;
  };
  [[nodiscard]] virtual auto GetPointData(float t) const noexcept -> PointData;
};

template<class T>
class ModifiedFunction : public IParametricFunction2d
{
public:
  using ModifierFunction = std::function<Point2dFlt(float t, const PointData& pointData)>;

  ModifiedFunction(const T& mainFunction, const ModifierFunction& modifierFunction) noexcept;

  [[nodiscard]] auto GetPoint(float t) const noexcept -> Point2dFlt override;

private:
  const T m_mainFunction;
  const ModifierFunction m_modifierFunction;
};

class LineFunction : public IParametricFunction2d
{
public:
  LineFunction(const Point2dFlt& startPos, const Point2dFlt& endPos) noexcept;

  [[nodiscard]] auto GetPoint(float t) const noexcept -> Point2dFlt override;

private:
  const Point2dFlt m_startPos;
  const Point2dFlt m_endPos;
};

struct AngleParams
{
  float startAngleInRadians = 0.0F;
  float endAngleInRadians   = TWO_PI;
};

class CircleFunction : public IParametricFunction2d
{
public:
  enum class Direction
  {
    CLOCKWISE,
    COUNTER_CLOCKWISE
  };

  CircleFunction(const Vec2dFlt& centrePos,
                 float radius,
                 const AngleParams& angleParams,
                 Direction direction = Direction::COUNTER_CLOCKWISE) noexcept;

  [[nodiscard]] auto GetPoint(float t) const noexcept -> Point2dFlt override;

private:
  const Vec2dFlt m_centrePos;
  const float m_radius;
  const AngleParams m_angleParams;
  const Direction m_direction;
  [[nodiscard]] auto GetPointAtAngle(float angle) const noexcept -> Point2dFlt;
};

class SpiralFunction : public IParametricFunction2d
{
public:
  enum class Direction
  {
    CLOCKWISE,
    COUNTER_CLOCKWISE
  };

  SpiralFunction(const Vec2dFlt& centrePos,
                 uint32_t numTurns,
                 Direction direction,
                 float minRadius,
                 float maxRadius) noexcept;

  [[nodiscard]] auto GetPoint(float t) const noexcept -> Point2dFlt override;
  [[nodiscard]] auto GetPointData(float t) const noexcept -> PointData override;

private:
  const Vec2dFlt m_centrePos;
  const float m_minRadius;
  const float m_maxRadius;
  const float m_angleFactor;
  [[nodiscard]] static auto GetSpiralPoint(float radius, float angle) noexcept -> Point2dFlt;
};

class LissajousFunction : public IParametricFunction2d
{
public:
  struct Params
  {
    float a;
    float b;
    float kX;
    float kY;
  };

  LissajousFunction(const Vec2dFlt& centrePos,
                    const AngleParams& angleParams,
                    const Params& params) noexcept;

  [[nodiscard]] auto GetPoint(float t) const noexcept -> Point2dFlt override;

private:
  const Vec2dFlt m_centrePos;
  const AngleParams m_angleParams;
  const Params m_params;
  [[nodiscard]] auto GetPointAtAngle(float angle) const noexcept -> Point2dFlt;
};

class HypotrochoidFunction : public IParametricFunction2d
{
public:
  struct Params
  {
    float bigR;
    float smallR;
    float height;
    float amplitude;
  };

  HypotrochoidFunction(const Vec2dFlt& centrePos,
                       const AngleParams& angleParams,
                       const Params& params) noexcept;

  [[nodiscard]] auto GetPoint(float t) const noexcept -> Point2dFlt override;

private:
  const Vec2dFlt m_centrePos;
  const AngleParams m_angleParams;
  const Params m_params;
  const float m_rDiff;
  const float m_numCusps;
  [[nodiscard]] static auto GetNumCusps(float bigR, float smallR) noexcept -> float;
  [[nodiscard]] auto GetPointAtAngle(float angle) const noexcept -> Point2dFlt;
};

class EpicycloidFunction : public IParametricFunction2d
{
public:
  struct Params
  {
    float k;
    float smallR;
    float amplitude;
  };

  EpicycloidFunction(const Vec2dFlt& centrePos,
                     const AngleParams& angleParams,
                     const Params& params) noexcept;

  [[nodiscard]] auto GetPoint(float t) const noexcept -> Point2dFlt override;

private:
  const Vec2dFlt m_centrePos;
  const AngleParams m_angleParams;
  const Params m_params;
  const float m_numCusps;
  [[nodiscard]] static auto GetNumCusps(float k) noexcept -> float;
  [[nodiscard]] auto GetPointAtAngle(float angle) const noexcept -> Point2dFlt;
};

class SineFunction : public IParametricFunction2d
{
public:
  struct Params
  {
    float amplitude = 1.0;
    float freq      = 1.0;
  };

  SineFunction(const Point2dFlt& startPos, const Point2dFlt& endPos, const Params& params) noexcept;

  [[nodiscard]] auto GetPoint(float t) const noexcept -> Point2dFlt override;

private:
  const Point2dFlt m_startPos;
  const Point2dFlt m_endPos;
  const Params m_params;
  const float m_distance;
  const float m_rotateAngle;
};

class OscillatingFunction : public IParametricFunction2d
{
public:
  struct Params
  {
    float oscillatingAmplitude = 1.0;
    float xOscillatingFreq     = 1.0;
    float yOscillatingFreq     = 1.0;
  };

  OscillatingFunction(const Point2dFlt& startPos,
                      const Point2dFlt& endPos,
                      const Params& params) noexcept;

  auto SetParams(const Params& params) noexcept -> void;
  auto SetStartPos(const Point2dFlt& startPos) noexcept -> void;
  auto SetEndPos(const Point2dFlt& endPos) noexcept -> void;
  auto SetAllowOscillatingPath(bool val) noexcept -> void;

  [[nodiscard]] auto GetPoint(float t) const noexcept -> Point2dFlt override;

private:
  bool m_allowOscillatingPath = true;
  Params m_params;
  Point2dFlt m_startPos;
  Point2dFlt m_endPos;
  [[nodiscard]] auto GetAdjustedStartPos(const Point2dFlt& startPos) const noexcept -> Point2dFlt;
  [[nodiscard]] auto GetOscillatingPoint(const Point2dFlt& linearPoint, float t) const noexcept
      -> Point2dFlt;
  [[nodiscard]] auto GetOscillatingOffset(float t) const noexcept -> Vec2dFlt;
};

template<class T>
inline ModifiedFunction<T>::ModifiedFunction(const T& mainFunction,
                                             const ModifierFunction& modifierFunction) noexcept
  : m_mainFunction{mainFunction}, m_modifierFunction{modifierFunction}
{
}

template<class T>
inline auto ModifiedFunction<T>::GetPoint(const float t) const noexcept -> Point2dFlt
{
  return m_modifierFunction(t, m_mainFunction.GetPointData(t));
}

inline LineFunction::LineFunction(const Point2dFlt& startPos, const Point2dFlt& endPos) noexcept
  : m_startPos{startPos}, m_endPos{endPos}
{
}

inline auto LineFunction::GetPoint(const float t) const noexcept -> Point2dFlt
{
  return lerp(m_startPos, m_endPos, t);
}

inline auto CircleFunction::GetPoint(const float t) const noexcept -> Point2dFlt
{
  const auto currentAngle =
      STD20::lerp(m_angleParams.startAngleInRadians, m_angleParams.endAngleInRadians, t);
  return GetPointAtAngle(currentAngle);
}

inline auto SpiralFunction::GetPoint(const float t) const noexcept -> Point2dFlt
{
  const auto radius = STD20::lerp(m_minRadius, m_maxRadius, t);
  const auto angle  = m_angleFactor * t;
  return GetSpiralPoint(radius, angle) + m_centrePos;
}

inline auto SpiralFunction::GetPointData(const float t) const noexcept -> PointData
{
  const auto radius = STD20::lerp(m_minRadius, m_maxRadius, t);
  const auto angle  = m_angleFactor * t;
  const auto point  = GetSpiralPoint(radius, angle) + m_centrePos;

  return {point, angle};
}

inline auto SpiralFunction::GetSpiralPoint(const float radius, const float angle) noexcept
    -> Point2dFlt
{
  return Point2dFlt{+radius * std::cos(angle), -radius * std::sin(angle)};
}

inline auto LissajousFunction::GetPoint(const float t) const noexcept -> Point2dFlt
{
  const auto currentAngle =
      STD20::lerp(m_angleParams.startAngleInRadians, m_angleParams.endAngleInRadians, t);
  return GetPointAtAngle(currentAngle);
}

inline auto HypotrochoidFunction::GetPoint(const float t) const noexcept -> Point2dFlt
{
  const auto currentAngle =
      STD20::lerp(m_angleParams.startAngleInRadians, m_angleParams.endAngleInRadians, t);
  return GetPointAtAngle(m_numCusps * currentAngle);
}

inline auto EpicycloidFunction::GetPoint(const float t) const noexcept -> Point2dFlt
{
  const auto currentAngle =
      STD20::lerp(m_angleParams.startAngleInRadians, m_angleParams.endAngleInRadians, t);
  return GetPointAtAngle(m_numCusps * currentAngle);
}

inline auto OscillatingFunction::SetAllowOscillatingPath(const bool val) noexcept -> void
{
  m_allowOscillatingPath = val;
}

inline auto OscillatingFunction::SetParams(const Params& params) noexcept -> void
{
  m_params = params;
}

inline auto OscillatingFunction::SetStartPos(const GOOM::Point2dFlt& startPos) noexcept -> void
{
  m_startPos = GetAdjustedStartPos(startPos);
}

inline auto OscillatingFunction::SetEndPos(const Point2dFlt& endPos) noexcept -> void
{
  m_endPos = endPos;
}

} // namespace GOOM::UTILS::MATH
