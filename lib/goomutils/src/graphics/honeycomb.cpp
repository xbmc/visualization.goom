#include "graphics/honeycomb.h"

#include "graphics/small_image_bitmaps.h"
#include "graphics/turtle.h"

#include <cmath>
#include <cstdint>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace UTILS
{
#else
namespace GOOM::UTILS
{
#endif

Honeycomb::Honeycomb(const uint32_t screenWidth,
                     const uint32_t screenHeight,
                     const Turtle::DrawFuncs& drawFuncs,
                     const uint32_t numCircles,
                     const uint32_t hexSize,
                     const uint32_t circleSize)
  : m_turtle{screenWidth, screenHeight, drawFuncs},
    m_numCircles{numCircles},
    m_hexSize{static_cast<int32_t>(hexSize)},
    m_circleSize{static_cast<int32_t>(circleSize)}
{
}

/**
inline void Honeycomb::SetDimensions(const uint32_t numCircles, const uint32_t size)
{
  m_numCircles = numCircles;
  m_circleSize = static_cast<int32_t>(size);
}
 **/

void Honeycomb::StartDrawCircle(uint32_t circleNum)
{
  m_segNum = 0;
  m_currentCircleNum = circleNum;
}

auto Honeycomb::IsCircleDone() const -> bool
{
  //  return m_segNum >= 6;
  return m_segNum >= m_numCircleSegments;
}

void Honeycomb::DrawNextCircleSegment()
{
  StartNextCircleSegment();
  while (!IsNextCircleSegmentFinished())
  {
    DrawNextHexShape();
  }
  FinishNextCircleSegment();
}

void Honeycomb::FinishDrawCircle()
{
  Move(-m_circleSize, +HEX_ANGLE);
  Move(+m_circleSize, -2.0 * HEX_ANGLE);
  Move(0, +HEX_ANGLE);
}

void Honeycomb::StartNextCircleSegment()
{
  m_segNum++;
  m_shapeNum = 0;
  Move(0, HEX_ANGLE);
}

void Honeycomb::DrawHexShape()
{
  m_turtle.PenDown();
  m_turtle.SetPenColor(m_getColors.getColors(m_currentCircleNum, m_turtle.GetPos()));

  // m_turtle.begin_fill()
  DoHexShape(m_hexSize);
  DoHexShapeInterior();
  //m_turtle.end_fill();

  m_turtle.PenUp();
}

void Honeycomb::FinishNextCircleSegment()
{
  Move(-m_circleSize, 0.0);
}

void Honeycomb::GotoHexCentre(const V2dInt& pos)
{
  GetTurtle().GotoPos({pos.x, pos.y + m_hexSize});
}

inline void Honeycomb::DoHexShape(const int32_t hexSize)
{
  constexpr int NUM_HEX_SIDES = 6;
  for (int i = 0; i < NUM_HEX_SIDES; i++)
  {
    Move(hexSize, -HEX_ANGLE);
  }
}

inline void Honeycomb::DoHexShapeInterior()
{
  m_turtle.PenUp();
  const V2dInt currentPos = m_turtle.GetPos();
  const float currentHeading = m_turtle.GetHeading();

  Move(m_hexSize, -120.0);
  m_turtle.PenDown();
  m_turtle.SetPenColor(m_getColors.getInnerColors(m_currentCircleNum, m_turtle.GetPos()));
  m_turtle.Image(SmallImageBitmaps::ImageNames::SPHERE, static_cast<uint32_t>(1 + m_hexSize) / 2);

  m_turtle.PenUp();
  m_turtle.GotoPos(currentPos);
  m_turtle.SetHeading(currentHeading);
}

void Honeycomb::DrawCentre()
{
  m_turtle.PenUp();
  m_turtle.GotoHome();

  DrawHexShape();
  Move(m_circleSize, -HEX_ANGLE);
  Move(m_circleSize, -HEX_ANGLE);
  Move(m_circleSize, -HEX_ANGLE);
  Move(0, 3.0 * HEX_ANGLE);
}

#if __cplusplus <= 201402L
} // namespace UTILS
} // namespace GOOM
#else
} // namespace GOOM::UTILS
#endif
