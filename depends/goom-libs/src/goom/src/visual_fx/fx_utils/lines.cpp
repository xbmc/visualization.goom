#include "lines.h"

#include "goom_config.h"
#include "utils/math/misc.h"

#include <format>

namespace GOOM::VISUAL_FX::FX_UTILS
{

using UTILS::MATH::FloatsEqual;
using UTILS::MATH::HALF_PI;
using UTILS::MATH::TWO_PI;

auto GetHorizontalLinePoints(const uint32_t numPoints, const uint32_t width, const float yValue)
    -> std::vector<LinePoint>
{
  Expects(numPoints > 1);

  auto linePoints = std::vector<LinePoint>(numPoints);

  const auto xStep = static_cast<float>(width - 1) / static_cast<float>(numPoints - 1);
  auto x           = 0.0F;
  for (auto& pt : linePoints)
  {
    pt.angle   = HALF_PI;
    pt.point.x = x;
    pt.point.y = yValue;

    x += xStep;
  }

  return linePoints;
}

auto GetVerticalLinePoints(const uint32_t numPoints, const uint32_t height, const float xValue)
    -> std::vector<LinePoint>
{
  Expects(numPoints > 1);

  auto linePoints = std::vector<LinePoint>(numPoints);

  const auto yStep = static_cast<float>(height - 1) / static_cast<float>(numPoints - 1);
  auto y           = 0.0F;
  for (auto& pt : linePoints)
  {
    pt.angle   = 0.0F;
    pt.point.x = xValue;
    pt.point.y = y;

    y += yStep;
  }

  return linePoints;
}

inline auto RoundToTwoDecimals(const double x) -> double
{
  static constexpr auto TEN_TO_THE_TWO = 100.0;
  return std::round(x * TEN_TO_THE_TWO) / TEN_TO_THE_TWO;
}

auto GetCircularLinePoints(const uint32_t numPoints,
                           const uint32_t width,
                           const uint32_t height,
                           const float radius) -> std::vector<LinePoint>
{
  Expects(numPoints > 1);

  auto linePoint = std::vector<LinePoint>(numPoints);

  const auto xCentre = 0.5 * static_cast<double>(width);
  const auto yCentre = 0.5 * static_cast<double>(height);

  const auto angleStep = static_cast<double>(TWO_PI) / static_cast<double>(numPoints - 1);
  auto angle           = 0.0;
  for (auto i = 0U; i < numPoints; ++i)
  {
    linePoint[i].angle   = static_cast<float>(RoundToTwoDecimals(angle));
    linePoint[i].point.x = static_cast<float>(
        RoundToTwoDecimals(xCentre + (static_cast<double>(radius) * std::cos(angle))));
    linePoint[i].point.y = static_cast<float>(
        RoundToTwoDecimals(yCentre + (static_cast<double>(radius) * std::sin(angle))));
    angle += angleStep;
  }

  Ensures(FloatsEqual(linePoint[0].point.x, linePoint[linePoint.size() - 1].point.x));
  Ensures(FloatsEqual(linePoint[0].point.y, linePoint[linePoint.size() - 1].point.y));

  return linePoint;
}

} // namespace GOOM::VISUAL_FX::FX_UTILS
