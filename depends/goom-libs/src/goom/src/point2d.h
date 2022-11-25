#pragma once

#include "utils/math/misc.h"

#include <cmath>
#include <cstdint>

namespace GOOM
{

struct Point2dFlt;
struct Vec2dInt;
struct Vec2dFlt;

struct Point2dInt
{
  int32_t x                       = 0;
  int32_t y                       = 0;
  constexpr Point2dInt() noexcept = default;
  constexpr Point2dInt(int32_t xx, int32_t yy) noexcept;
  constexpr Point2dInt(uint32_t xx, uint32_t yy) noexcept;
  [[nodiscard]] constexpr auto ToFlt() const noexcept -> Point2dFlt;
  constexpr auto Translate(const Vec2dInt& vec) noexcept -> void;
};

[[nodiscard]] constexpr auto operator==(const Point2dInt& point1, const Point2dInt& point2) noexcept
    -> bool;
[[nodiscard]] constexpr auto operator!=(const Point2dInt& point1, const Point2dInt& point2) noexcept
    -> bool;
[[nodiscard]] constexpr auto operator+(const Point2dInt& point, const Vec2dInt& vec) noexcept
    -> Point2dInt;
[[nodiscard]] constexpr auto operator-(const Point2dInt& point, const Vec2dInt& vec) noexcept
    -> Point2dInt;
[[nodiscard]] constexpr auto operator+(const Point2dInt& point, int32_t scalar) noexcept
    -> Point2dInt;
[[nodiscard]] constexpr auto operator-(const Point2dInt& point, int32_t scalar) noexcept
    -> Point2dInt;
[[nodiscard]] auto lerp(const Point2dInt& point1, const Point2dInt& point2, float t) noexcept
    -> Point2dInt;
[[nodiscard]] constexpr auto midpoint(const Point2dInt& point1, const Point2dInt& point2) noexcept
    -> Point2dInt;
[[nodiscard]] constexpr auto MidpointFromOrigin(const Point2dInt& point) noexcept -> Point2dInt;
[[nodiscard]] auto Distance(const Point2dInt& point1, const Point2dInt& point2) noexcept -> int32_t;
[[nodiscard]] auto SqDistance(const Point2dInt& point1, const Point2dInt& point2) noexcept
    -> int32_t;

struct Vec2dInt
{
  int32_t x                     = 0;
  int32_t y                     = 0;
  constexpr Vec2dInt() noexcept = default;
  constexpr Vec2dInt(int32_t xx, int32_t yy) noexcept;
  constexpr Vec2dInt(uint32_t xx, uint32_t yy) noexcept;
  constexpr explicit Vec2dInt(const Point2dInt& point) noexcept;
  [[nodiscard]] constexpr auto ToFlt() const noexcept -> Vec2dFlt;
  constexpr auto operator+=(const Vec2dInt& vec) noexcept -> Vec2dInt&;
};
[[nodiscard]] constexpr auto operator==(const Vec2dInt& vec1, const Vec2dInt& vec2) noexcept
    -> bool;
[[nodiscard]] constexpr auto operator+(const Vec2dInt& vec1, const Vec2dInt& vec2) noexcept
    -> Vec2dInt;
[[nodiscard]] constexpr auto operator-(const Vec2dInt& vec1, const Vec2dInt& vec2) noexcept
    -> Vec2dInt;
[[nodiscard]] constexpr auto operator+(const Vec2dInt& vec1, int32_t scalar) noexcept -> Vec2dInt;
[[nodiscard]] constexpr auto operator-(const Vec2dInt& vec1, int32_t scalar) noexcept -> Vec2dInt;

struct Point2dFlt
{
  float x                         = 0.0F;
  float y                         = 0.0F;
  constexpr Point2dFlt() noexcept = default;
  constexpr Point2dFlt(float xx, float yy) noexcept;
  [[nodiscard]] auto ToInt() const noexcept -> Point2dInt;
  constexpr auto Translate(const Vec2dFlt& vec) noexcept -> void;
  constexpr auto Translate(float scalar) noexcept -> void;
  constexpr auto Scale(float scalar) noexcept -> void;
  auto Rotate(float angle) noexcept -> void;
};

[[nodiscard]] constexpr auto operator+(const Point2dFlt& point, const Vec2dFlt& vec) noexcept
    -> Point2dFlt;
[[nodiscard]] constexpr auto operator-(const Point2dFlt& point, const Vec2dFlt& vec) noexcept
    -> Point2dFlt;
[[nodiscard]] constexpr auto operator+(const Point2dFlt& point, float scalar) noexcept
    -> Point2dFlt;
[[nodiscard]] constexpr auto operator-(const Point2dFlt& point, float scalar) noexcept
    -> Point2dFlt;
[[nodiscard]] constexpr auto operator-(float scalar, const Point2dFlt& point) noexcept
    -> Point2dFlt;
[[nodiscard]] constexpr auto lerp(const Point2dFlt& point1,
                                  const Point2dFlt& point2,
                                  float t) noexcept -> Point2dFlt;
[[nodiscard]] auto Distance(const Point2dFlt& point1, const Point2dFlt& point2) noexcept -> float;
[[nodiscard]] auto SqDistance(const Point2dFlt& point1, const Point2dFlt& point2) noexcept -> float;

struct Vec2dFlt
{
  float x                       = 0.0F;
  float y                       = 0.0F;
  constexpr Vec2dFlt() noexcept = default;
  constexpr Vec2dFlt(float xx, float yy) noexcept;
  constexpr explicit Vec2dFlt(const Point2dFlt& point) noexcept;
  [[nodiscard]] auto ToInt() const noexcept -> Vec2dInt;
  constexpr auto operator+=(const Vec2dFlt& vec) noexcept -> Vec2dFlt&;
};
[[nodiscard]] constexpr auto operator+(const Vec2dFlt& vec1, const Vec2dFlt& vec2) noexcept
    -> Vec2dFlt;
[[nodiscard]] constexpr auto operator-(const Vec2dFlt& vec1, const Vec2dFlt& vec2) noexcept
    -> Vec2dFlt;
[[nodiscard]] constexpr auto operator+(const Vec2dFlt& vec, float scalar) noexcept -> Vec2dFlt;
[[nodiscard]] constexpr auto operator-(const Vec2dFlt& vec, float scalar) noexcept -> Vec2dFlt;
[[nodiscard]] constexpr auto operator*(float scale, const Vec2dFlt& vec) noexcept -> Vec2dFlt;

constexpr Point2dInt::Point2dInt(const int32_t xx, const int32_t yy) noexcept : x{xx}, y{yy}
{
}

constexpr Point2dInt::Point2dInt(const uint32_t xx, const uint32_t yy) noexcept
  : x{static_cast<int32_t>(xx)}, y{static_cast<int32_t>(yy)}
{
}

constexpr auto Point2dInt::ToFlt() const noexcept -> Point2dFlt
{
  return {static_cast<float>(x), static_cast<float>(y)};
}

constexpr auto Point2dInt::Translate(const Vec2dInt& vec) noexcept -> void
{
  x += vec.x;
  y += vec.y;
}

constexpr auto operator==(const Point2dInt& point1, const Point2dInt& point2) noexcept -> bool
{
  return (point1.x == point2.x) && (point1.y == point2.y);
}

constexpr auto operator!=(const Point2dInt& point1, const Point2dInt& point2) noexcept -> bool
{
  return not(point1 == point2);
}

constexpr auto operator+(const Point2dInt& point, const Vec2dInt& vec) noexcept -> Point2dInt
{
  return {point.x + vec.x, point.y + vec.y};
}

constexpr auto operator-(const Point2dInt& point, const Vec2dInt& vec) noexcept -> Point2dInt
{
  return {point.x - vec.x, point.y - vec.y};
}

constexpr auto operator+(const Point2dInt& point, const int32_t scalar) noexcept -> Point2dInt
{
  return {point.x + scalar, point.y + scalar};
}

constexpr auto operator-(const Point2dInt& point, const int32_t scalar) noexcept -> Point2dInt
{
  return {point.x - scalar, point.y - scalar};
}

constexpr Vec2dInt::Vec2dInt(const int32_t xx, const int32_t yy) noexcept : x{xx}, y{yy}
{
}

constexpr Vec2dInt::Vec2dInt(const uint32_t xx, const uint32_t yy) noexcept
  : x{static_cast<int32_t>(xx)}, y{static_cast<int32_t>(yy)}
{
}

constexpr Vec2dInt::Vec2dInt(const Point2dInt& point) noexcept : x{point.x}, y{point.y}
{
}

constexpr auto Vec2dInt::ToFlt() const noexcept -> Vec2dFlt
{
  return {static_cast<float>(x), static_cast<float>(y)};
}

constexpr auto operator==(const Vec2dInt& vec1, const Vec2dInt& vec2) noexcept -> bool
{
  return (vec1.x == vec2.x) && (vec1.y == vec2.y);
}

constexpr auto Vec2dInt::operator+=(const Vec2dInt& vec) noexcept -> Vec2dInt&
{
  x += vec.x;
  y += vec.y;
  return *this;
}

constexpr auto operator+(const Vec2dInt& vec1, const Vec2dInt& vec2) noexcept -> Vec2dInt
{
  return {vec1.x + vec2.x, vec1.y + vec2.y};
}

constexpr auto operator-(const Vec2dInt& vec1, const Vec2dInt& vec2) noexcept -> Vec2dInt
{
  return {vec1.x - vec2.x, vec1.y - vec2.y};
}

constexpr auto operator+(const Vec2dInt& vec1, const int32_t scalar) noexcept -> Vec2dInt
{
  return {vec1.x + scalar, vec1.y + scalar};
}

constexpr auto operator-(const Vec2dInt& vec1, const int32_t scalar) noexcept -> Vec2dInt
{
  return {vec1.x - scalar, vec1.y - scalar};
}

constexpr Point2dFlt::Point2dFlt(const float xx, const float yy) noexcept : x{xx}, y{yy}
{
}

inline auto Point2dFlt::ToInt() const noexcept -> Point2dInt
{
  return {static_cast<int32_t>(std::round(x)), static_cast<int32_t>(std::round(y))};
}

constexpr auto Point2dFlt::Translate(const Vec2dFlt& vec) noexcept -> void
{
  x += vec.x;
  y += vec.y;
}

constexpr auto Point2dFlt::Translate(const float scalar) noexcept -> void
{
  x += scalar;
  y += scalar;
}

inline auto Point2dFlt::Rotate(const float angle) noexcept -> void
{
  const float sinAngle = std::sin(angle);
  const float cosAngle = std::cos(angle);
  const float xNext    = (x * cosAngle) - (y * sinAngle);
  y                    = (x * sinAngle) + (y * cosAngle);
  x                    = xNext;
}

constexpr auto Point2dFlt::Scale(const float scalar) noexcept -> void
{
  x *= scalar;
  y *= scalar;
}

constexpr auto operator+(const Point2dFlt& point, const Vec2dFlt& vec) noexcept -> Point2dFlt
{
  return {point.x + vec.x, point.y + vec.y};
}

constexpr auto operator-(const Point2dFlt& point, const Vec2dFlt& vec) noexcept -> Point2dFlt
{
  return {point.x - vec.x, point.y - vec.y};
}

constexpr auto operator+(const Point2dFlt& point, const float scalar) noexcept -> Point2dFlt
{
  return {point.x + scalar, point.y + scalar};
}

constexpr auto operator-(const Point2dFlt& point, const float scalar) noexcept -> Point2dFlt
{
  return {point.x - scalar, point.y - scalar};
}

constexpr auto operator-(float scalar, const Point2dFlt& point) noexcept -> Point2dFlt
{
  return {scalar - point.x, scalar - point.y};
}

constexpr auto operator*(const float scalar, const Point2dFlt& point) noexcept -> Point2dFlt
{
  return {scalar * point.x, scalar * point.y};
}

constexpr Vec2dFlt::Vec2dFlt(const float xx, const float yy) noexcept : x{xx}, y{yy}
{
}

constexpr Vec2dFlt::Vec2dFlt(const Point2dFlt& point) noexcept : x{point.x}, y{point.y}
{
}

inline auto Vec2dFlt::ToInt() const noexcept -> Vec2dInt
{
  return {static_cast<int32_t>(std::round(x)), static_cast<int32_t>(std::round(y))};
}

constexpr auto Vec2dFlt::operator+=(const Vec2dFlt& vec) noexcept -> Vec2dFlt&
{
  x += vec.x;
  y += vec.y;
  return *this;
}

constexpr auto operator+(const Vec2dFlt& vec1, const Vec2dFlt& vec2) noexcept -> Vec2dFlt
{
  return {vec1.x + vec2.x, vec1.y + vec2.y};
}

constexpr auto operator-(const Vec2dFlt& vec1, const Vec2dFlt& vec2) noexcept -> Vec2dFlt
{
  return {vec1.x - vec2.x, vec1.y - vec2.y};
}

constexpr auto operator+(const Vec2dFlt& vec, const float scalar) noexcept -> Vec2dFlt
{
  return {vec.x + scalar, vec.y + scalar};
}

constexpr auto operator-(const Vec2dFlt& vec, const float scalar) noexcept -> Vec2dFlt
{
  return {vec.x - scalar, vec.y - scalar};
}

constexpr auto operator*(const float scale, const Vec2dFlt& vec) noexcept -> Vec2dFlt
{
  return {scale * vec.x, scale * vec.y};
}

inline auto lerp(const Point2dInt& point1, const Point2dInt& point2, const float t) noexcept
    -> Point2dInt
{
  return {
      static_cast<int32_t>(
          std::round(STD20::lerp(static_cast<float>(point1.x), static_cast<float>(point2.x), t))),
      static_cast<int32_t>(
          std::round(STD20::lerp(static_cast<float>(point1.y), static_cast<float>(point2.y), t))),
  };
}

constexpr auto lerp(const Point2dFlt& point1, const Point2dFlt& point2, const float t) noexcept
    -> Point2dFlt
{
  return {
      STD20::lerp(point1.x, point2.x, t),
      STD20::lerp(point1.y, point2.y, t),
  };
}

constexpr auto midpoint(const Point2dInt& point1, const Point2dInt& point2) noexcept -> Point2dInt
{
  return {STD20::midpoint(point1.x, point2.x), STD20::midpoint(point1.y, point2.y)};
}

constexpr auto MidpointFromOrigin(const Point2dInt& point) noexcept -> Point2dInt
{
  return {STD20::midpoint(0, point.x), STD20::midpoint(0, point.y)};
}

inline auto Distance(const Point2dInt& point1, const Point2dInt& point2) noexcept -> int32_t
{
  return static_cast<int32_t>(std::lround(Distance(point1.ToFlt(), point2.ToFlt())));
}

inline auto Distance(const Point2dFlt& point1, const Point2dFlt& point2) noexcept -> float
{
  return std::sqrt(UTILS::MATH::SqDistance(point1.x - point2.x, point1.y - point2.y));
}

inline auto SqDistance(const Point2dInt& point1, const Point2dInt& point2) noexcept -> int32_t
{
  return UTILS::MATH::SqDistance(point1.x - point2.x, point1.y - point2.y);
}

inline auto SqDistance(const Point2dFlt& point1, const Point2dFlt& point2) noexcept -> float
{
  return UTILS::MATH::SqDistance(point1.x - point2.x, point1.y - point2.y);
}

} // namespace GOOM
