#pragma once

#include "point2d.h"

#include <cstdint>
#include <vector>

namespace GOOM::VISUAL_FX::TENTACLES
{

class CirclesTentacleLayout
{
public:
  CirclesTentacleLayout(float startRadius, float endRadius, uint32_t numTentacles) noexcept;

  [[nodiscard]] auto GetNumTentacles() const noexcept -> uint32_t;

  [[nodiscard]] auto GetStartPoints() const noexcept -> const std::vector<Point2dFlt>&;
  [[nodiscard]] auto GetEndPoints() const noexcept -> const std::vector<Point2dFlt>&;

  [[nodiscard]] auto GetStartRadius() const noexcept -> float;
  [[nodiscard]] auto GetEndRadius() const noexcept -> float;

  [[nodiscard]] static auto GetCirclePoints(float radius, uint32_t numPoints) noexcept
      -> std::vector<Point2dFlt>;

private:
  const std::vector<Point2dFlt> m_startPoints;
  const std::vector<Point2dFlt> m_endPoints;
  const float m_startRadius;
  const float m_endRadius;
};

inline auto CirclesTentacleLayout::GetNumTentacles() const noexcept -> uint32_t
{
  return static_cast<uint32_t>(m_startPoints.size());
}

inline auto CirclesTentacleLayout::GetStartPoints() const noexcept -> const std::vector<Point2dFlt>&
{
  return m_startPoints;
}

inline auto CirclesTentacleLayout::GetEndPoints() const noexcept -> const std::vector<Point2dFlt>&
{
  return m_endPoints;
}

inline auto CirclesTentacleLayout::GetStartRadius() const noexcept -> float
{
  return m_startRadius;
}

inline auto CirclesTentacleLayout::GetEndRadius() const noexcept -> float
{
  return m_endRadius;
}

} // namespace GOOM::VISUAL_FX::TENTACLES
