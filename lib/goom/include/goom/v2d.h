#ifndef VISUALIZATION_GOOM_V2D_H
#define VISUALIZATION_GOOM_V2D_H

#include "goomutils/mathutils.h"

#include <cmath>
#include <cstdint>

namespace GOOM
{

struct V2dFlt;

struct V2dInt
{
  int32_t x = 0;
  int32_t y = 0;
  [[nodiscard]] auto ToFlt() const -> V2dFlt;
  auto operator+=(const V2dInt& v) -> V2dInt&;
};

[[nodiscard]] auto operator+(const V2dInt& v1, const V2dInt& v2) -> V2dInt;
auto lerp(const V2dInt& p0, const V2dInt& p1, float t) -> V2dInt;

struct V2dFlt
{
  float x = 0.0;
  float y = 0.0;
  V2dFlt() noexcept = default;
  V2dFlt(float xx, float yy) noexcept;
  auto operator+=(const V2dFlt& v) -> V2dFlt&;
  auto operator+=(float scalar) -> V2dFlt&;
  auto operator-=(const V2dFlt& v) -> V2dFlt&;
  auto operator*=(float scalar) -> V2dFlt&;
  auto operator*(float a) const -> V2dFlt;
};

[[nodiscard]] auto operator+(const V2dFlt& v1, const V2dFlt& v2) -> V2dFlt;
[[nodiscard]] auto operator-(const V2dFlt& v1, const V2dFlt& v2) -> V2dFlt;
[[nodiscard]] auto operator*(float a, const V2dFlt& v) -> V2dFlt;
auto lerp(const V2dFlt& p0, const V2dFlt& p1, float t) -> V2dFlt;


inline auto V2dInt::ToFlt() const -> V2dFlt
{
  return {static_cast<float>(x), static_cast<float>(y)};
}

inline auto V2dInt::operator+=(const V2dInt& v) -> V2dInt&
{
  x += v.x;
  y += v.y;
  return *this;
}

inline auto operator+(const V2dInt& v1, const V2dInt& v2) -> V2dInt
{
  return {v1.x + v2.x, v1.y + v2.y};
}

inline auto operator-(const V2dInt& v1, const V2dInt& v2) -> V2dInt
{
  return {v1.x - v2.x, v1.y - v2.y};
}

inline V2dFlt::V2dFlt(const float xx, const float yy) noexcept : x{xx}, y{yy}
{
}

inline auto V2dFlt::operator+=(const V2dFlt& v) -> V2dFlt&
{
  x += v.x;
  y += v.y;
  return *this;
}

inline auto V2dFlt::operator-=(const V2dFlt& v) -> V2dFlt&
{
  x += -v.x;
  y += -v.y;
  return *this;
}

inline auto V2dFlt::operator+=(const float scalar) -> V2dFlt&
{
  x += scalar;
  y += scalar;
  return *this;
}

inline auto V2dFlt::operator*=(const float scalar) -> V2dFlt&
{
  x *= scalar;
  y *= scalar;
  return *this;
}

inline auto operator+(const V2dFlt& v1, const V2dFlt& v2) -> V2dFlt
{
  return {v1.x + v2.x, v1.y + v2.y};
}

inline auto V2dFlt::operator*(const float a) const -> V2dFlt
{
  return V2dFlt{a * x, a * y};
}

inline auto operator*(const float a, const V2dFlt& v) -> V2dFlt
{
  return v * a;
}

inline auto lerp(const V2dInt& p0, const V2dInt& p1, const float t) -> V2dInt
{
  return {
      static_cast<int32_t>(
          std::round(stdnew::lerp(static_cast<float>(p0.x), static_cast<float>(p1.x), t))),
      static_cast<int32_t>(
          std::round(stdnew::lerp(static_cast<float>(p0.y), static_cast<float>(p1.y), t))),
  };
}

inline auto lerp(const V2dFlt& p0, const V2dFlt& p1, float t) -> V2dFlt
{
  return {
      stdnew::lerp(static_cast<float>(p0.x), static_cast<float>(p1.x), t),
      stdnew::lerp(static_cast<float>(p0.y), static_cast<float>(p1.y), t),
  };
}

} // namespace GOOM
#endif
