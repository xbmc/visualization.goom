#include "randutils.h"

//#undef NO_LOGGING

#include "logging.h"
#include "splitmix.hpp"
#include "utils/math/misc.h"
#include "xoshiro.hpp"

#include <cstdint>
#include <format>
#include <limits>
#include <ostream>
#include <random>
#include <stdexcept>

namespace GOOM::UTILS::MATH::RAND
{

const uint32_t G_RAND_MAX = (xoshiro256plus64::max() > std::numeric_limits<uint32_t>::max())
                                ? std::numeric_limits<uint32_t>::max()
                                : static_cast<uint32_t>(xoshiro256plus64::max());

// NOTE: C++ std::uniform_int_distribution is too expensive (about double time) so we use
// Xoshiro and multiplication/shift technique. For timings, see tests/test_goomrand.cpp.
// thread_local xoshiro256starstar64 eng { GetRandSeed() };

static uint64_t randSeed = std::random_device{}();
thread_local xoshiro256plus64 xoshiroEng{GetRandSeed()};

auto GetXoshiroEng() -> xoshiro256plus64
{
  return xoshiroEng;
}

auto GetRandSeed() -> uint64_t
{
  return randSeed;
}

void SetRandSeed(const uint64_t seed)
{
  randSeed   = seed;
  xoshiroEng = GetRandSeed();
  LogDebug("SetRandSeed: xoshiroEng = {}", GetRandSeed()); // NOLINT
}

inline auto RandXoshiroFunc(const uint32_t n0, const uint32_t n1) -> uint32_t
{
  const auto x     = static_cast<uint32_t>(xoshiroEng());
  const uint64_t m = (static_cast<uint64_t>(x) * static_cast<uint64_t>(n1 - n0)) >> 32;
  return n0 + static_cast<uint32_t>(m);
}

inline auto RandSplitMixFunc(const uint32_t n0, const uint32_t n1) -> uint32_t
{
  // thread_local SplitMix32 eng { GetRandSeed() };
  thread_local splitmix64 s_eng{GetRandSeed()};
  const auto x     = static_cast<uint32_t>(s_eng());
  const uint64_t m = (static_cast<uint64_t>(x) * static_cast<uint64_t>(n1 - n0)) >> 32;
  return n0 + static_cast<uint32_t>(m);
}

void SaveRandState(std::ostream& file)
{
  file << randSeed << "\n";
  file << xoshiroEng << "\n";
}

void RestoreRandState(std::istream& file)
{
  file >> randSeed;
  file >> xoshiroEng;
}

auto GetRandInRange(const uint32_t n0, const uint32_t n1) -> uint32_t
{
#ifndef NDEBUG
  if (n0 >= n1)
  {
    throw std::logic_error(std20::format("uint n0:'{}' >= n1:'{}'", n0, n1));
  }
#endif

  return RandXoshiroFunc(n0, n1);
}

auto GetRandInRange(const int32_t n0, const int32_t n1) -> int32_t
{
  if (n0 >= n1)
  {
    throw std::logic_error(std20::format("int n0:'{}' >= n1:'{}'", n0, n1));
  }
  if ((n0 >= 0) && (n1 >= 0))
  {
    return static_cast<int32_t>(
        GetRandInRange(static_cast<uint32_t>(n0), static_cast<uint32_t>(n1)));
  }
  return n0 + static_cast<int32_t>(GetNRand(static_cast<uint32_t>(-n0 + n1)));
}

auto GetRandInRange(const float x0, const float x1) -> float
{
#ifndef NDEBUG
  if (x0 >= x1)
  {
    throw std::logic_error(std20::format("float x0:'{}' >= x1:'{}'", x0, x1));
  }
#endif

  static const auto s_ENG_MAX = static_cast<float>(G_RAND_MAX);
  const float t               = static_cast<float>(RandXoshiroFunc(0, G_RAND_MAX)) / s_ENG_MAX;
  return STD20::lerp(x0, x1, t);
  //  thread_local std::uniform_real_distribution<> dis(0, 1);
  //  return std::lerp(x0, x1, static_cast<float>(dis(eng)));
}

} // namespace GOOM::UTILS::MATH::RAND
