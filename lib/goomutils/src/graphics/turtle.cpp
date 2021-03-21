/*
 * Fachhochschule Erfurt https://ai.fh-erfurt.de
 * Fachrichtung Angewandte Informatik
 * Project: Turtleizer_CPP (static C++ library for Windows)
 *
 * Object class, representing one Turtle (of potentially many) within the
 * simple C++ emulation of the Turtleizer module coming with Structorizer
 * (http://structorizer.fisch.lu).
 * The intention is that several separately controllable (and subclassible)
 * Turtle objects may be created to share the drawing area.
 *
 * Author: Kay G�rtzig
 * Version: 11.0.0 (covering capabilities of Structorizer 3.31, functional GUI)
 *
 * History (add at top):
 * --------------------------------------------------------
 * 2021-04-06   VERSION 11.0.0: Method draw decomposed to support memory HDC / bitblt
 * 2021-04-05   VERSION 11.0.0: New method for SVG export, nearest point search
 * 2021-04-02   VERSION 11.0.0: Enh. #6 (tracking of the bounds and new internal methods)
 * 2019-07-08   VERSION 10.0.1: Fixed #1 (environment-dependent char array type), #2, #3
 * 2018-10-23   VERSION 10.0.0: Casts added to avoid compiler warnings.
 * 2018-07-30   VERSION 9: API adaptation to Structorizer 3.28-07: clear() procedure
 * 2017-10-29   New methods getX(), getY(), getOrientation() implemented
 * 2016-12-09   Created for VERSION 6
 */

#include "graphics/turtle.h"

#include "goom/goom_draw.h"
#include "goom/v2d.h"

#include <cassert>
#include <cmath>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace UTILS
{
#else
namespace GOOM::UTILS
{
#endif

Turtle::Turtle(const uint32_t screenWidth, const uint32_t screenHeight, const DrawFuncs& drawFuncs)
  : m_screenWidth{static_cast<int32_t>(screenWidth)},
    m_screenHeight{static_cast<int32_t>(screenHeight)},
    m_drawFuncs{drawFuncs},
    m_offset{0, 0},
    m_pos{0, 0},
    m_heading{0.0},
    m_elements{},
    m_defaultColours{std::vector<Pixel>{Pixel::BLACK}},
    m_defaultThickness{1},
    m_lastDrawn{m_elements.cend()},
    m_nDrawn{0},
    m_penDown{true}
{
}

Turtle::~Turtle() = default;

// Make the turtle move the given number of pixels forward.
void Turtle::Forward(const int32_t dist, const Pixel& color, const uint8_t thickness)
{
  Forward(dist, std::vector<Pixel>{color}, thickness);
}

void Turtle::Forward(const int32_t dist, const std::vector<Pixel>& colors, const uint8_t thickness)
{
  // FIXME: correct the angle
  const V2dInt oldP{m_pos};
  const double angle = M_PI * (90 + m_heading) / 180.0;
  m_pos.x += static_cast<int32_t>(std::round(static_cast<double>(dist) * std::cos(angle)));
  m_pos.y -= static_cast<int32_t>(std::round(static_cast<double>(dist) * std::sin(angle)));
  if (m_penDown)
  {
    m_elements.push_back(TurtleLine{oldP, m_pos, colors, thickness});
    if (m_elements.size() == 1)
    {
      m_lastDrawn = m_elements.cbegin();
    }
    m_drawFuncs.drawLine(oldP.x, oldP.y, m_pos.x, m_pos.y, colors, thickness);
  }
}

void Turtle::Circle(const int radius)
{
  m_drawFuncs.drawCircle(m_offset.x + m_pos.x, m_offset.y + m_pos.y, radius, m_defaultColours,
                         m_defaultThickness);
}

void Turtle::Image(SmallImageBitmaps::ImageNames imageName, const uint32_t size)
{
  m_drawFuncs.drawSmallImage(m_offset.x + m_pos.x, m_offset.y + m_pos.y, imageName, size,
                             m_defaultColours);
}

// Sets the turtle to the position (x, y).
void Turtle::GotoPos(const V2dInt& pos)
{
  const V2dInt oldP{m_pos};
  m_pos = pos;
  if (m_penDown)
  {
    Draw(TurtleLine{oldP, m_pos, m_defaultColours, m_defaultThickness});
  }
}

// Rotates the turtle to the left by some angle (degrees!).
void Turtle::Left(const float degrees)
{
  // FIXME: Normalise angle
  m_heading += degrees;
}

// Wipes all drawn content of this turtle
void Turtle::Clear()
{
  m_elements.clear();
  m_lastDrawn = m_elements.cend();
  m_nDrawn = 0;
}

// Returns the current orientation in degrees from North (clockwise = positive)
auto Turtle::GetHeading() const -> float
{
  return m_heading;
  // TODO: Test the correct results
  float ori = m_heading;
  while (ori > 180)
  {
    ori -= 360;
  }
  while (ori < -180)
  {
    ori += 360;
  }
  return -ori;
}

auto Turtle::GetNearestPoint(const V2dInt& coord,
                             const bool betweenEnds,
                             const int32_t radius,
                             V2dInt& nearest) const -> int32_t
{
  int32_t minDist = -1;
  for (const auto& element : m_elements)
  {
    V2dInt candidate;
    const int32_t dist = element.GetNearestPoint(coord, betweenEnds, candidate);
    if (dist == 0)
    {
      nearest = candidate;
      return dist;
    }
    if (dist < radius && (minDist < 0 || dist < minDist))
    {
      nearest = candidate;
      minDist = dist;
    }
  }
  return minDist;
}

void Turtle::Draw(const bool drawAll)
{
  return;
  // START KGU 2021-04-05: issue #6 performance improvement
  //for (Elements::const_iterator it(this->elements.cbegin()); it != this->elements.cend(); ++it)
  //{
  //	it->draw(gr);
  //}

  if (drawAll)
  {
    m_nDrawn = 0;
    m_lastDrawn = m_elements.cbegin();
  }

  const size_t nElements = m_elements.size();
  if (nElements == m_nDrawn)
  {
    return;
  }

  auto it(m_lastDrawn);
  if (m_nDrawn > 0)
  {
    ++it;
  }

  for (; m_nDrawn < nElements; ++it, m_nDrawn++)
  {
    Draw(*it);
    if (m_nDrawn > 0)
    {
      ++m_lastDrawn;
    }
  }
}

void Turtle::SetOffset(const V2dInt& pos)
{
  m_offset = pos;
}

void Turtle::Draw(const Turtle::TurtleLine& line) const
{
  const int xFrom = m_offset.x + line.GetFrom().x;
  const int yFrom = m_offset.y + line.GetFrom().y;
  const int xTo = m_offset.x + line.GetTo().x;
  const int yTo = m_offset.y + line.GetTo().y;
  m_drawFuncs.drawLine(xFrom, yFrom, xTo, yTo, line.GetColors(), line.GetThickness());
}

auto Turtle::HasElements() const -> bool
{
  return !m_elements.empty();
}

Turtle::TurtleLine::TurtleLine(const V2dInt& from,
                               const V2dInt& to,
                               const std::vector<Pixel>& colors,
                               const uint8_t thickness)
  : m_posFrom(from), m_posTo(to), m_colors{colors}, m_thickness{thickness}
{
}

auto Turtle::TurtleLine::GetNearestPoint(const V2dInt& pt,
                                         const bool betweenEnds,
                                         V2dInt& nearest) const -> int32_t
{
  if (betweenEnds)
  {
    // We abuse a point for the direction vector
    const V2dInt dvec{m_posTo.x - m_posFrom.x, m_posTo.y - m_posFrom.y};
    const V2dInt pvec{pt.x - m_posFrom.x, pt.x - m_posFrom.y};
    const int32_t dlen2 = (dvec.x * dvec.x + dvec.y * dvec.y);
    const int32_t param = (pvec.x * dvec.x + pvec.y * dvec.y) / dlen2;
    if (param < 0)
    {
      nearest.x = m_posFrom.x;
      nearest.y = m_posFrom.y;
    }
    else if (param * param > dlen2)
    {
      nearest.x = m_posTo.x;
      nearest.y = m_posTo.y;
    }
    else
    {
      nearest.x = m_posFrom.x + param * dvec.x;
      nearest.y = m_posFrom.y + param * dvec.y;
    }
    const int32_t distX = nearest.x - pt.x;
    const int32_t distY = nearest.y - pt.y;
    return static_cast<int32_t>(
        std::sqrt(std::round(static_cast<float>(distX * distX + distY * distY))));
  }

  int32_t distX = m_posFrom.x - pt.x;
  int32_t distY = m_posFrom.y - pt.y;
  const auto dist1 = static_cast<int32_t>(
      std::sqrt(std::round(static_cast<float>(distX * distX + distY * distY))));
  distX = m_posTo.x - pt.x;
  distY = m_posTo.y - pt.y;
  const auto dist2 = static_cast<int32_t>(
      std::sqrt(std::round(static_cast<float>(distX * distX + distY * distY))));
  if (dist2 > dist1)
  {
    nearest.x = m_posFrom.x;
    nearest.y = m_posFrom.y;
    return dist1;
  }

  nearest.x = m_posTo.x;
  nearest.y = m_posTo.y;
  return dist2;
}

#if __cplusplus <= 201402L
} // namespace UTILS
} // namespace GOOM
#else
} // namespace GOOM::UTILS
#endif
