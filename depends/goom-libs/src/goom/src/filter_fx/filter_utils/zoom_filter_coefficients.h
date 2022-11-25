#pragma once

#include "goom_config.h"
#include "goom_graphic.h"
#include "utils/math/misc.h"

#include <algorithm>
#include <array>
#include <cstdint>

namespace GOOM::FILTER_FX::FILTER_UTILS::ZOOM_FILTER_COEFFS
{

static constexpr auto DIM_FILTER_COEFFS_EXP = 4U;
static constexpr auto DIM_FILTER_COEFFS     = UTILS::MATH::PowerOf2(DIM_FILTER_COEFFS_EXP);
static constexpr auto DIM_FILTER_COEFFS_MOD_MASK = DIM_FILTER_COEFFS - 1U;
static constexpr auto MAX_SUM_COEFFS = UTILS::MATH::Sq(DIM_FILTER_COEFFS);
static constexpr auto NUM_NEIGHBOR_COEFFS        = 4U;

using NeighborhoodPixelArray = std::array<Pixel, NUM_NEIGHBOR_COEFFS>;
using NeighborhoodCoeffArray = std::array<uint32_t, NUM_NEIGHBOR_COEFFS>;
using FilterCoeff2dArray =
    std::array<std::array<NeighborhoodCoeffArray, DIM_FILTER_COEFFS>, DIM_FILTER_COEFFS>;
using FilterCoeff2dArrayPtrs =
    std::array<std::array<const NeighborhoodCoeffArray*, DIM_FILTER_COEFFS>, DIM_FILTER_COEFFS>;

constexpr auto GetNeighborhoodCoeffArray(const uint32_t coeffH, const uint32_t coeffV) noexcept
    -> NeighborhoodCoeffArray
{
  const auto maxMinusCoeffH = DIM_FILTER_COEFFS - coeffH;
  const auto maxMinusCoeffV = DIM_FILTER_COEFFS - coeffV;

  // clang-format off
  auto coeffs = std::array<uint32_t, NUM_NEIGHBOR_COEFFS>{
      maxMinusCoeffH * maxMinusCoeffV,
      coeffH         * maxMinusCoeffV,
      maxMinusCoeffH * coeffV,
      coeffH         * coeffV
  };
  // clang-format on

  // Get the sum and check it.
  // TODO(glk) - Can use std::accumulate with C++20.
  // Ensures(std::accumulate(cbegin(coeffs), cend(coeffs), 0U) == channel_limits<uint32_t>::max());
  auto coeffsSum = 0U;
  for (const auto& coeff : coeffs)
  {
    coeffsSum += coeff;
  }
  UNUSED_FOR_NDEBUG(coeffsSum);
  Ensures(coeffsSum == MAX_SUM_COEFFS);

  /**
  LogInfo("{:2}, {:2}:  {:3}, {:3}, {:3}, {:3} - sum: {:3}",
          coeffH,
          coeffV,
          coeffs[0],
          coeffs[1],
          coeffs[2],
          coeffs[3],
          std::accumulate(cbegin(coeffs), cend(coeffs), 0U)); // NOLINT
  **/

  return coeffs;
}

// Modif d'optim by Jeko : precalcul des 4 coeffs resultant des 2 pos.
// Modification of optim by Jeko: pre-calculation of the 4 coeffs resulting from the 2 positions.
constexpr auto GetPrecalculatedCoefficientArray() noexcept -> FilterCoeff2dArray
{
  auto precalculatedCoeffs = FilterCoeff2dArray{};

  for (auto coeffH = 0U; coeffH < DIM_FILTER_COEFFS; ++coeffH)
  {
    for (auto coeffV = 0U; coeffV < DIM_FILTER_COEFFS; ++coeffV)
    {
      precalculatedCoeffs[coeffH][coeffV] = GetNeighborhoodCoeffArray(coeffH, coeffV);
    }
  }

  return precalculatedCoeffs;
}

inline constexpr auto PRECALCULATED_COEFF_ARRAY = GetPrecalculatedCoefficientArray();

constexpr auto GetPrecalculatedCoefficientPtrs() noexcept -> FilterCoeff2dArrayPtrs
{
  auto precalculatedCoeffPtrs = FilterCoeff2dArrayPtrs{};

  for (auto coeffH = 0U; coeffH < DIM_FILTER_COEFFS; ++coeffH)
  {
    for (auto coeffV = 0U; coeffV < DIM_FILTER_COEFFS; ++coeffV)
    {
      precalculatedCoeffPtrs[coeffH][coeffV] = &PRECALCULATED_COEFF_ARRAY[coeffH][coeffV];
    }
  }

  return precalculatedCoeffPtrs;
}

inline constexpr auto PRECALCULATED_COEFF_PTRS = GetPrecalculatedCoefficientPtrs();

} // namespace GOOM::FILTER_FX::FILTER_UTILS::ZOOM_FILTER_COEFFS
