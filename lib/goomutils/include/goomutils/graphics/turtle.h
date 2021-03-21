#ifndef VISUALIZATION_GOOM_LIB_GOOMUTILS_TURTLE_H
#define VISUALIZATION_GOOM_LIB_GOOMUTILS_TURTLE_H

#include "goom/goom_draw.h"
#include "goom/v2d.h"
#include "goomutils/graphics/small_image_bitmaps.h"

#include <cstdint>
#include <list>
#include <vector>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace UTILS
{
#else
namespace GOOM::UTILS
{
#endif

class Turtle
{
public:
  using DrawLineFunc = std::function<void(
      int x1, int y1, int x2, int y2, const std::vector<Pixel>& colors, uint8_t thickness)>;
  using DrawCircleFunc = std::function<void(
      int x, int y, int radius, const std::vector<Pixel>& colors, uint8_t thickness)>;
  using DrawSmallImageFunc = std::function<void(int xMid,
                                                int yMid,
                                                UTILS::SmallImageBitmaps::ImageNames imageName,
                                                uint32_t size,
                                                const std::vector<Pixel>& colors)>;

  struct DrawFuncs
  {
    DrawLineFunc drawLine;
    DrawCircleFunc drawCircle;
    DrawSmallImageFunc drawSmallImage;
  };

  Turtle(uint32_t screenWidth, uint32_t screenHeight, const DrawFuncs& drawFuncs);
  virtual ~Turtle();

  void Clear();

  auto GetOffset() const -> const V2dInt&;
  void SetOffset(const V2dInt& pos);

  void Circle(int radius);
  void Image(SmallImageBitmaps::ImageNames imageName, uint32_t size);

  // Make the turtle move the given number of pixels forward (or backward if negative)
  // using current pen colour.
  void Forward(int32_t dist);

  // Make the turtle move the given number of pixels forward (or backward if negative)
  // using given colour.
  void Forward(int32_t dist, const Pixel& color, uint8_t thickness);
  void Forward(int32_t dist, const std::vector<Pixel>& colors, uint8_t thickness);

  // Make the turtle move the given number of pixels forward (or backward if negative)
  // using current pen colour.
  void Backward(int32_t dist);

  // Make the turtle move the given number of pixels forward (or backward if negative)
  // using given colour.
  void Backward(int32_t dist, const Pixel& col, uint8_t thickness);

  // Rotates the turtle to the left by an angle.
  void Left(float degrees);

  // Rotates the turtle to the right by an angle.
  void Right(float degrees);

  // The turtle lifts the pen up, so when moving no line will be drawn.
  void PenUp();

  // The turtle sets the pen down, so a line is being drawn when moving.
  void PenDown();

  // Sets the default pen colour (used for moves without color argument).
  void SetPenColor(const Pixel& color);
  void SetPenColor(const std::vector<Pixel>& colors);

  void SetPenThickness(uint8_t thickness);

  void SetHeading(float degrees);

  // Sets the turtle to the position (X,Y).
  void GotoPos(const V2dInt& pos);

  // Sets the X-coordinate of the turtle's position to a new value.
  void GotoX(int32_t x);

  // Sets the Y-coordinate of the turtle's position to a new value.
  void GotoY(int32_t y);

  void GotoHome();

  auto GetScreenWidth() const -> int32_t;
  auto GetScreenHeight() const -> int32_t;
  auto GetXMax() const -> int32_t;
  auto GetYMax() const -> int32_t;
  auto GetPenColors() const -> const std::vector<Pixel>&;
  auto GetPos() const -> const V2dInt&;
  auto GetX() const -> int32_t;
  auto GetY() const -> int32_t;
  auto GetHeading() const -> float;

  // Searches the nearest end point or point on line within the given radius to
  // given coordinate, returns its distance or -1 and puts its coordinates into
  // point nearest (if such a point was found). (The result may be ambiguous.)
  auto GetNearestPoint(const V2dInt& coord, bool betweenEnds, int32_t radius, V2dInt& nearest) const
      -> int32_t;

  // Draws the trajectory of this turtle
  void Draw(bool drawAll = true);

  // Reports whether this turtle has any drawn elements
  auto HasElements() const -> bool;

private:
  // Internal class tracking a line drawn by the turtle (for onPaint())
  class TurtleLine
  {
  public:
    TurtleLine(const V2dInt& from,
               const V2dInt& to,
               const std::vector<Pixel>& colors,
               uint8_t thickness);

    inline auto GetFrom() const -> const V2dInt& { return m_posFrom; }
    inline auto GetTo() const -> const V2dInt& { return m_posTo; }
    inline auto GetColors() const -> const std::vector<Pixel>& { return m_colors; }
    inline auto GetThickness() const -> uint8_t { return m_thickness; }

    /* Identifies the nearest end point or point on line to the given
     * coordinate pt, returns its distance or -1 and puts its coordinates into
     * point nearest. */
    auto GetNearestPoint(const V2dInt& pt, bool betweenEnds, V2dInt& nearest) const -> int32_t;

  private:
    const V2dInt m_posFrom;
    const V2dInt m_posTo;
    std::vector<Pixel> m_colors;
    const uint8_t m_thickness;
  };

  using Elements = std::list<TurtleLine>;
  const int32_t m_screenWidth;
  const int32_t m_screenHeight;
  DrawFuncs m_drawFuncs;
  V2dInt m_offset;
  V2dInt m_pos; // current turtle position
  float m_heading; // current orientation in degrees
  Elements m_elements; // List of lines drawn in this session
  std::vector<Pixel> m_defaultColours; // Default colour for line segments without explicit colour
  uint8_t m_defaultThickness;
  Elements::const_iterator m_lastDrawn; // Iterator to the last drawn element
  uint32_t m_nDrawn; // Number of drawn elements so far
  bool m_penDown; // Whether the pen is ready to draw

  void Draw(const TurtleLine& line) const;
};

inline auto Turtle::GetScreenWidth() const -> int32_t
{
  return m_screenWidth;
}

inline auto Turtle::GetScreenHeight() const -> int32_t
{
  return m_screenHeight;
}

inline auto Turtle::GetXMax() const -> int32_t
{
  return GetScreenWidth() - 1;
}

inline auto Turtle::GetYMax() const -> int32_t
{
  return GetScreenHeight() - 1;
}

inline auto Turtle::GetOffset() const -> const V2dInt&
{
  return m_offset;
}

inline auto Turtle::GetPenColors() const -> const std::vector<Pixel>&
{
  return m_defaultColours;
}

inline auto Turtle::GetPos() const -> const V2dInt&
{
  return m_pos;
}

inline auto Turtle::GetX() const -> int32_t
{
  return m_pos.x;
}

inline auto Turtle::GetY() const -> int32_t
{
  return m_pos.y;
}

inline void Turtle::GotoX(const int32_t x)
{
  GotoPos({x, m_pos.y});
}

inline void Turtle::GotoY(const int32_t y)
{
  GotoPos({m_pos.x, y});
}

inline void Turtle::GotoHome()
{
  GotoPos({0, 0});
}

inline void Turtle::Forward(const int32_t dist)
{
  Forward(dist, m_defaultColours, m_defaultThickness);
}

inline void Turtle::Backward(const int32_t dist)
{
  Forward(-dist);
}

inline void Turtle::Backward(const int32_t dist, const Pixel& col, const uint8_t thickness)
{
  Forward(-dist, col, thickness);
}

inline void Turtle::Right(const float degrees)
{
  Left(-degrees);
}

inline void Turtle::PenUp()
{
  m_penDown = false;
}

inline void Turtle::PenDown()
{
  m_penDown = true;
}

inline void Turtle::SetHeading(const float degrees)
{
  m_heading = degrees;
}

inline void Turtle::SetPenColor(const Pixel& color)
{
  m_defaultColours = std::vector<Pixel>{color};
}

inline void Turtle::SetPenColor(const std::vector<Pixel>& colors)
{
  m_defaultColours = colors;
}

inline void Turtle::SetPenThickness(const uint8_t thickness)
{
  m_defaultThickness = thickness;
}

#if __cplusplus <= 201402L
} // namespace UTILS
} // namespace GOOM
#else
} // namespace GOOM::UTILS
#endif
#endif // VISUALIZATION_GOOM_LIB_GOOMUTILS_TURTLE_H
