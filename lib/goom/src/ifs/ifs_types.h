#ifndef VISUALIZATION_GOOM_IFS_TYPES_H
#define VISUALIZATION_GOOM_IFS_TYPES_H

#include <cstdint>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace IFS
{
#else
namespace GOOM::IFS
{
#endif

using Dbl = float;
using Flt = int;

struct FltPoint
{
  Flt x = 0;
  Flt y = 0;
};

constexpr int32_t FIX = 12;

inline auto DblToFlt(const Dbl x) -> Flt
{
  constexpr int32_t UNIT = 1 << FIX;
  return static_cast<Flt>(static_cast<Dbl>(UNIT) * x);
}

inline auto DivByUnit(const Flt x) -> Flt
{
  return x >> FIX;
}

inline auto DivBy2Units(const Flt x) -> Flt
{
  return x >> (FIX + 1);
}

#if __cplusplus <= 201402L
} // namespace IFS
} // namespace GOOM
#else
} // namespace GOOM::IFS
#endif

#endif //VISUALIZATION_GOOM_IFS_TYPES_H
