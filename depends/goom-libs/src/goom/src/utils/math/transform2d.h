#pragma once

#include "misc.h"
#include "point2d.h"

#include <cmath>

namespace GOOM::UTILS::MATH
{

class Transform2d
{
public:
  Transform2d() noexcept = default;
  Transform2d(float angleInRadians, float scale, const Vec2dFlt& translation) noexcept;

  auto SetRotation(float angleInRadians) -> void;
  auto SetScale(float scale) -> void;
  auto SetTranslation(const Vec2dFlt& translation) -> void;

  [[nodiscard]] auto GetTransformedPoint(const Point2dInt& point) const -> Point2dInt;
  [[nodiscard]] auto GetTransformedPoint(const Point2dFlt& point) const -> Point2dFlt;

private:
  float m_rotationAngle = 0.0F;
  float m_scale         = 1.0F;
  Vec2dFlt m_translation{};
  float m_sinRotationAngle = std::sin(m_rotationAngle);
  float m_cosRotationAngle = std::cos(m_rotationAngle);
  bool m_rotationAngleSet  = not FloatsEqual(0.0F, m_rotationAngle);
  bool m_scaleSet          = not FloatsEqual(1.0F, m_scale);
  bool m_translationSet =
      (not FloatsEqual(0.0F, m_translation.x)) || (not FloatsEqual(0.0F, m_translation.y));
};

inline Transform2d::Transform2d(const float angleInRadians,
                                const float scale,
                                const Vec2dFlt& translation) noexcept
  : m_rotationAngle{angleInRadians}, m_scale{scale}, m_translation{translation}
{
}

inline auto Transform2d::SetRotation(const float angleInRadians) -> void
{
  m_rotationAngle    = angleInRadians;
  m_rotationAngleSet = not FloatsEqual(0.0F, m_rotationAngle);
  m_sinRotationAngle = std::sin(m_rotationAngle);
  m_cosRotationAngle = std::cos(m_rotationAngle);
}

inline auto Transform2d::SetScale(const float scale) -> void
{
  m_scale    = scale;
  m_scaleSet = not FloatsEqual(1.0F, m_scale);
}

inline auto Transform2d::SetTranslation(const Vec2dFlt& translation) -> void
{
  m_translation = translation;
  m_translationSet =
      (not FloatsEqual(0.0F, m_translation.x)) || (not FloatsEqual(0.0F, m_translation.y));
}

inline auto Transform2d::GetTransformedPoint(const Point2dInt& point) const -> Point2dInt
{
  return GetTransformedPoint(point.ToFlt()).ToInt();
}

inline auto Transform2d::GetTransformedPoint(const Point2dFlt& point) const -> Point2dFlt
{
  auto transformedPoint = Point2dFlt{};

  if (not m_rotationAngleSet)
  {
    transformedPoint = point;
  }
  else
  {
    transformedPoint.x = (point.x * m_cosRotationAngle) - (point.y * m_sinRotationAngle);
    transformedPoint.y = (point.x * m_sinRotationAngle) + (point.y * m_cosRotationAngle);
  }

  if (m_scaleSet)
  {
    transformedPoint.Scale(m_scale);
  }

  if (m_translationSet)
  {
    transformedPoint.Translate(m_translation);
  }

  return transformedPoint;
}

} // namespace GOOM::UTILS::MATH
