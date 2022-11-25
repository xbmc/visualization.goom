#pragma once

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>

#if __cplusplus > 201703L
#pragma message("WARNING " __FILE__ " is obsolete when compiling with C++20. Use std math headers.")
#endif

namespace STD20
{
template<typename T>
inline constexpr auto pi_v = static_cast<T>(3.14159265358979323846264);
inline constexpr double pi = pi_v<double>;

template<typename _Tp>
constexpr _Tp midpoint(_Tp __a, _Tp __b) noexcept
{
  if constexpr (std::is_integral_v<_Tp>)
  {
    using _Up = std::make_unsigned_t<_Tp>;

    int __k  = 1;
    auto __m = static_cast<_Up>(__a);
    auto __M = static_cast<_Up>(__b);
    if (__a > __b)
    {
      __k = -1;
      __m = static_cast<_Up>(__b);
      __M = static_cast<_Up>(__a);
    }
    return __a + __k * _Tp(_Up(__M - __m) / 2);
  }
  else // is_floating
  {
    constexpr _Tp __lo = std::numeric_limits<_Tp>::min() * 2;
    constexpr _Tp __hi = std::numeric_limits<_Tp>::max() / 2;
    const _Tp __abs_a  = __a < 0 ? -__a : __a;
    const _Tp __abs_b  = __b < 0 ? -__b : __b;
    if (__abs_a <= __hi && __abs_b <= __hi)
      return (__a + __b) / 2; // always correctly rounded
    if (__abs_a < __lo) // not safe to halve __a
      return __a + __b / 2;
    if (__abs_b < __lo) // not safe to halve __b
      return __a / 2 + __b;
    return __a / 2 + __b / 2; // otherwise correctly rounded
  }
}

template<typename _Fp>
[[nodiscard]] constexpr _Fp __lerp(_Fp __a, _Fp __b, _Fp __t) noexcept
{
  if ((__a <= 0 && __b >= 0) || (__a >= 0 && __b <= 0))
  {
    return __t * __b + (1 - __t) * __a;
  }

  if (1 == __t)
  {
    return __b; // exact
  }

  // Exact at __t=0, monotonic except near __t=1,
  // bounded, determinate, and consistent:
  const _Fp __x = __a + __t * (__b - __a);
  return (__t > 1) == (__b > __a) ? (__b < __x ? __x : __b)
                                  : (__b > __x ? __x : __b); // monotonic near __t=1
}

[[nodiscard]] constexpr auto lerp(const float __a, const float __b, const float __t) noexcept
    -> float
{
  return __lerp(__a, __b, __t);
}
[[nodiscard]] constexpr auto lerp(const double __a, const double __b, const double __t) noexcept
    -> double
{
  return __lerp(__a, __b, __t);
}
[[nodiscard]] inline auto lerp(const uint32_t a, const uint32_t b, const float t) noexcept
    -> uint32_t
{
  return static_cast<uint32_t>(
      std::round(STD20::lerp(static_cast<float>(a), static_cast<float>(b), t)));
}
[[nodiscard]] inline auto lerp(const int32_t a, const int32_t b, const float t) noexcept -> int32_t
{
  return static_cast<int32_t>(
      std::round(STD20::lerp(static_cast<float>(a), static_cast<float>(b), t)));
}

} // namespace STD20
