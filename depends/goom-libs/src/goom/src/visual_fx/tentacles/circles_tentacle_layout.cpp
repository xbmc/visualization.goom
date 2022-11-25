#include "circles_tentacle_layout.h"

#include "point2d.h"
#include "utils/math/misc.h"

#include <vector>

namespace GOOM::VISUAL_FX::TENTACLES
{

using UTILS::MATH::HALF_PI;
using UTILS::MATH::TWO_PI;

static constexpr auto ANGLE_START  = HALF_PI;
static constexpr auto ANGLE_FINISH = ANGLE_START + TWO_PI;

CirclesTentacleLayout::CirclesTentacleLayout(const float startRadius,
                                             const float endRadius,
                                             const uint32_t numTentacles) noexcept
  : m_startPoints{GetCirclePoints(startRadius, numTentacles)},
    m_endPoints{GetCirclePoints(endRadius, numTentacles)},
    m_startRadius{startRadius},
    m_endRadius{endRadius}
{
}

auto CirclesTentacleLayout::GetCirclePoints(const float radius, const uint32_t numPoints) noexcept
    -> std::vector<Point2dFlt>
{
  auto circlePoints = std::vector<Point2dFlt>{};

  // TODO(glk) Use TValue
  const auto angleStep = (ANGLE_FINISH - ANGLE_START) / static_cast<float>(numPoints);
  auto angle           = ANGLE_START;

  for (auto i = 0U; i < numPoints; ++i)
  {
    const auto x = radius * std::cos(angle);
    const auto y = radius * std::sin(angle);

    circlePoints.emplace_back(x, y);

    angle += angleStep;
  }

  return circlePoints;
}

} // namespace GOOM::VISUAL_FX::TENTACLES
