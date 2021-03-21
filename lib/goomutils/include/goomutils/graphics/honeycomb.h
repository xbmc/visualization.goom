#ifndef VISUALIZATION_GOOM_HONEYCOMB_H
#define VISUALIZATION_GOOM_HONEYCOMB_H

#include "goom/goom_draw.h"
#include "goom/v2d.h"
#include "goomutils/graphics/turtle.h"

#include <cstdint>
#include <functional>
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

class Honeycomb
{
public:
  static constexpr size_t MAX_CIRCLES = 116;
  static constexpr int32_t MIN_SIZE = 2;
  using GetHexColorsFunc =
      std::function<auto(uint32_t circleNum, const V2dInt& pos)->std::vector<Pixel>>;
  struct ColorFuncs
  {
    GetHexColorsFunc getColors;
    GetHexColorsFunc getInnerColors;
  };
  Honeycomb(uint32_t screenWidth,
            uint32_t screenHeight,
            const Turtle::DrawFuncs& drawFuncs,
            uint32_t numCircles,
            uint32_t hexSize,
            uint32_t circleSize);

  auto GetTurtle() const -> const Turtle&;
  auto GetTurtle() -> Turtle&;

  [[nodiscard]] auto GetHexSize() const -> uint32_t;
  [[nodiscard]] auto GetCircleSize() const -> uint32_t;
  void SetCircleSize(uint32_t size);
  [[nodiscard]] auto GetNumCircles() const -> uint32_t;

  [[nodiscard]] auto GetClassicHoneycomb() const -> bool;
  void SetClassicHoneycomb(bool val);

  //void SetDimensions(uint32_t numCircles, uint32_t size);
  void SetGetColorsFunc(const ColorFuncs& getColor);
  void DrawCentre();

  static constexpr float MIN_CIRCLE_ANGLE = 1.0;
  static constexpr float MAX_CIRCLE_ANGLE = 60.0;
  auto GetCurrentCircleAngle() const -> float;
  void SetCurrentCircleAngle(float degrees);

  static constexpr uint32_t MIN_NUM_CIRCLE_SEGMENTS = 20;
  static constexpr uint32_t MAX_NUM_CIRCLE_SEGMENTS = 50;
  auto GetCurrentNumCircleSegments() const -> uint32_t;
  void SetCurrentNumCircleSegments(uint32_t n);

  void StartDrawCircle(uint32_t circleNum);
  auto GetCurrentCircleNum() const -> uint32_t;
  void DrawNextCircleSegment();
  auto IsCircleDone() const -> bool;
  void FinishDrawCircle();

  void GotoHexCentre(const V2dInt& pos);

  void SetSegmentSize(uint32_t val);
  void StartNextCircleSegment();
  void DrawNextHexShape();
  auto IsNextCircleSegmentFinished() const -> bool;
  void FinishNextCircleSegment();

private:
  static constexpr float HEX_ANGLE = 60.0;
  Turtle m_turtle;
  ColorFuncs m_getColors{};
  const uint32_t m_numCircles;
  const int32_t m_hexSize;
  bool m_classicHoneycomb = false;
  int32_t m_circleSize;
  uint32_t m_currentCircleNum = 0;
  float m_currentCircleAngle = 1.0;
  uint32_t m_segNum = 0;
  uint32_t m_segmentSize = 1;
  uint32_t m_numCircleSegments = 50;
  uint32_t m_shapeNum{};
  void DrawHexShape();
  void DoHexShape(int32_t hexSize);
  void DoHexShapeInterior();
  void Move(int32_t dist, float angle);
};

inline auto Honeycomb::GetTurtle() -> Turtle&
{
  return m_turtle;
}

inline auto Honeycomb::GetTurtle() const -> const Turtle&
{
  return m_turtle;
}

inline auto Honeycomb::GetNumCircles() const -> uint32_t
{
  return m_numCircles;
}

inline auto Honeycomb::GetHexSize() const -> uint32_t
{
  return static_cast<uint32_t>(m_hexSize);
}

inline auto Honeycomb::GetCircleSize() const -> uint32_t
{
  return static_cast<uint32_t>(m_circleSize);
}

inline void Honeycomb::SetCircleSize(const uint32_t size)
{
  m_circleSize = static_cast<int32_t>(size);
}

inline auto Honeycomb::GetClassicHoneycomb() const -> bool
{
  return m_classicHoneycomb;
}

inline void Honeycomb::SetClassicHoneycomb(const bool val)
{
  m_classicHoneycomb = val;
}

inline void Honeycomb::SetGetColorsFunc(const ColorFuncs& getColor)
{
  m_getColors = getColor;
}

inline auto Honeycomb::GetCurrentCircleNum() const -> uint32_t
{
  return m_currentCircleNum;
}

inline auto Honeycomb::GetCurrentCircleAngle() const -> float
{
  return m_currentCircleAngle;
}

inline void Honeycomb::SetCurrentCircleAngle(const float degrees)
{
  m_currentCircleAngle = degrees;
}

inline auto Honeycomb::GetCurrentNumCircleSegments() const -> uint32_t
{
  return m_numCircleSegments;
}

inline void Honeycomb::SetCurrentNumCircleSegments(const uint32_t n)
{
  m_numCircleSegments = n;
}

inline void Honeycomb::SetSegmentSize(const uint32_t val)
{
  m_segmentSize = val;
}

inline auto Honeycomb::IsNextCircleSegmentFinished() const -> bool
{
  return m_shapeNum >= m_currentCircleNum + 1;
}

inline void Honeycomb::DrawNextHexShape()
{
  for (uint32_t i = 0; i < m_segmentSize; i++)
  {
    if (IsNextCircleSegmentFinished())
    {
      break;
    }

    DrawHexShape();

    if (m_classicHoneycomb)
    {
      Move(m_circleSize, -m_currentCircleAngle);
      Move(m_circleSize, m_currentCircleAngle);
    }

    m_shapeNum++;
  }
}

inline void Honeycomb::Move(const int32_t dist, const float angle)
{
  m_turtle.Right(angle);
  m_turtle.Forward(dist);
}

#if __cplusplus <= 201402L
} // namespace UTILS
} // namespace GOOM
#else
} // namespace GOOM::UTILS
#endif
#endif //VISUALIZATION_GOOM_HONEYCOMB_H
