#pragma once

#include "goom_rand_base.h"
#include "randutils.h"

#include <cstdint>

namespace GOOM::UTILS::MATH
{

class GoomRand : public IGoomRand
{
public:
  [[nodiscard]] auto GetNRand(uint32_t n1) const noexcept -> uint32_t override;

  [[nodiscard]] auto GetRandInRange(uint32_t n0, uint32_t n1) const noexcept -> uint32_t override;
  [[nodiscard]] auto GetRandInRange(int32_t n0, int32_t n1) const noexcept -> int32_t override;
  [[nodiscard]] auto GetRandInRange(float n0, float n1) const noexcept -> float override;

  [[nodiscard]] auto ProbabilityOf(float x) const noexcept -> bool override;
};

inline auto GoomRand::GetNRand(const uint32_t n1) const noexcept -> uint32_t
{
  return RAND::GetNRand(n1);
}

inline auto GoomRand::GetRandInRange(const uint32_t n0, const uint32_t n1) const noexcept
    -> uint32_t
{
  return RAND::GetRandInRange(n0, n1);
}

inline auto GoomRand::GetRandInRange(const int32_t n0, const int32_t n1) const noexcept -> int32_t
{
  return RAND::GetRandInRange(n0, n1);
}

inline auto GoomRand::GetRandInRange(const float n0, const float n1) const noexcept -> float
{
  return RAND::GetRandInRange(n0, n1);
}

inline auto GoomRand::ProbabilityOf(const float x) const noexcept -> bool
{
  return RAND::ProbabilityOf(x);
}

} // namespace GOOM::UTILS::MATH
