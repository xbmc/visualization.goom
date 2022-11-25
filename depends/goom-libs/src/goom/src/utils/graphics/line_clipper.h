#pragma once

#include "point2d.h"

#include <cstdint>

namespace GOOM::UTILS::GRAPHICS
{

struct LineFlt
{
  Point2dFlt point1;
  Point2dFlt point2;
};

class LineClipper
{
public:
  struct ClipRectangle
  {
    float xMin;
    float yMin;
    float xMax;
    float yMax;
  };

  explicit constexpr LineClipper(const ClipRectangle& clipRectangle) noexcept;

  enum class ClipResult
  {
    INSIDE,
    CLIPPED,
    REJECTED
  };
  struct ClippedLine
  {
    ClipResult clipResult;
    LineFlt line;
  };

  [[nodiscard]] constexpr auto GetClippedLine(const LineFlt& line) const -> ClippedLine;

private:
  ClipRectangle m_clipRectangle;

  // The region codes relative to the clip rectangle.
  static constexpr auto INSIDE = static_cast<uint32_t>(0b0000);
  static constexpr auto LEFT   = static_cast<uint32_t>(0b0001);
  static constexpr auto RIGHT  = static_cast<uint32_t>(0b0010);
  static constexpr auto BOTTOM = static_cast<uint32_t>(0b0100);
  static constexpr auto TOP    = static_cast<uint32_t>(0b1000);
  [[nodiscard]] constexpr auto CohenSutherlandClip(const LineFlt& line) const noexcept
      -> ClippedLine;
  [[nodiscard]] constexpr auto ComputeCode(const Point2dFlt& point) const noexcept -> uint32_t;
  [[nodiscard]] constexpr auto GetIntersectionPoint(const LineFlt& line, uint32_t codeOutside) const
      -> Point2dFlt;
  [[nodiscard]] static constexpr auto GetXIntercept(float y, const LineFlt& line) -> float;
  [[nodiscard]] static constexpr auto GetYIntercept(float x, const LineFlt& line) -> float;
};

constexpr LineClipper::LineClipper(const ClipRectangle& clipRectangle) noexcept
  : m_clipRectangle{clipRectangle}
{
}

constexpr auto LineClipper::GetClippedLine(const LineFlt& line) const -> ClippedLine
{
  return CohenSutherlandClip(line);
}

// Function to compute region code for a point(x, y)
[[nodiscard]] constexpr auto LineClipper::ComputeCode(const Point2dFlt& point) const noexcept
    -> uint32_t
{
  auto code = INSIDE;

  if (point.x < m_clipRectangle.xMin) // to the left of rectangle
  {
    code |= LEFT;
  }
  else if (point.x > m_clipRectangle.xMax) // to the right of rectangle
  {
    code |= RIGHT;
  }

  if (point.y < m_clipRectangle.yMin) // below the rectangle
  {
    code |= BOTTOM;
  }
  else if (point.y > m_clipRectangle.yMax) // above the rectangle
  {
    code |= TOP;
  }

  return code;
}

// Implementing Cohen-Sutherland algorithm
// Clipping a line from P1 = (x2, y2) to P2 = (x2, y2)
[[nodiscard]] constexpr auto LineClipper::CohenSutherlandClip(const LineFlt& line) const noexcept
    -> ClippedLine
{
  auto newPoint1 = line.point1;
  auto newPoint2 = line.point2;

  // Compute the region codes for point1 and point2.
  auto code1 = ComputeCode(newPoint1);
  auto code2 = ComputeCode(newPoint2);

  if ((code1 == INSIDE) && (code2 == INSIDE))
  {
    // Both endpoints lie within the clip rectangle.
    return {
        ClipResult::INSIDE, {newPoint1, newPoint2}
    };
  }
  if (code1 & code2)
  {
    // Both endpoints are outside the clip rectangle.
    return {
        ClipResult::REJECTED, {newPoint1, newPoint2}
    };
  }

  // Some segment of the line lies within the clip rectangle.
  while (true)
  {
    // At least one endpoint is outside the clip rectangle, so get it.
    const auto codeOutside       = code1 != INSIDE ? code1 : code2;
    const auto intersectionPoint = GetIntersectionPoint({newPoint1, newPoint2}, codeOutside);

    // Replace the point outside the clip rectangle with the intersection point.
    if (codeOutside == code1)
    {
      newPoint1 = intersectionPoint;
      code1     = ComputeCode(newPoint1);
    }
    else
    {
      newPoint2 = intersectionPoint;
      code2     = ComputeCode(newPoint2);
    }

    if ((code1 == INSIDE) && (code2 == INSIDE))
    {
      // Both endpoints lie within the clip rectangle.
      break;
    }
    if (code1 & code2)
    {
      // Both endpoints are outside the clip rectangle.
      return {
          ClipResult::REJECTED, {newPoint1, newPoint2}
      };
    }
  }

  return {
      ClipResult::CLIPPED, {newPoint1, newPoint2}
  };
}

constexpr auto LineClipper::GetIntersectionPoint(const LineFlt& line,
                                                 const uint32_t codeOutside) const -> Point2dFlt
{
  auto intersectionPoint = Point2dFlt{};

  if (codeOutside & TOP)
  {
    // The intersection point is above the clip rectangle.
    intersectionPoint.y = m_clipRectangle.yMax;
    intersectionPoint.x = GetXIntercept(intersectionPoint.y, line);
  }
  else if (codeOutside & BOTTOM)
  {
    // The intersection point is below the clip rectangle.
    intersectionPoint.y = m_clipRectangle.yMin;
    intersectionPoint.x = GetXIntercept(intersectionPoint.y, line);
  }
  else if (codeOutside & RIGHT)
  {
    // The intersection point is to the right of the clip rectangle.
    intersectionPoint.x = m_clipRectangle.xMax;
    intersectionPoint.y = GetYIntercept(intersectionPoint.x, line);
  }
  else if (codeOutside & LEFT)
  {
    // The intersection point is to the left of the clip rectangle.
    intersectionPoint.x = m_clipRectangle.xMin;
    intersectionPoint.y = GetYIntercept(intersectionPoint.x, line);
  }
  else
  {
    FailFast();
  }

  return intersectionPoint;
}

// Get the x-intercept using the formula:
//     x = x1 + (1 / slope) * (y - y1)
constexpr auto LineClipper::GetXIntercept(const float y, const LineFlt& line) -> float
{
  const auto oneOverSlope = (line.point2.x - line.point1.x) / (line.point2.y - line.point1.y);
  return line.point1.x + (oneOverSlope * (y - line.point1.y));
}

// Get the y-intercept using the formula:
//     y = y1 + slope * (x - x1)
constexpr auto LineClipper::GetYIntercept(const float x, const LineFlt& line) -> float
{
  const auto slope = (line.point2.y - line.point1.y) / (line.point2.x - line.point1.x);
  return line.point1.y + (slope * (x - line.point1.x));
}

} // namespace GOOM::UTILS::GRAPHICS
