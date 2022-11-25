#pragma once

#include "filter_buffers.h"
#include "filter_utils/zoom_filter_coefficients.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "utils/math/goom_rand_base.h"
#include "utils/name_value_pairs.h"
#include "utils/timer.h"

#include <libdivide.h>
#include <string>

namespace GOOM::FILTER_FX
{

class FilterColorsService
{
public:
  FilterColorsService(const UTILS::MATH::IGoomRand& goomRand) noexcept;

  auto SetBrightness(float brightness) noexcept -> void;
  auto SetBuffSettings(const FXBuffSettings& settings) noexcept -> void;
  auto SetBlockyWavy(bool val) noexcept -> void;

  using NeighborhoodCoeffArray = FILTER_UTILS::ZOOM_FILTER_COEFFS::NeighborhoodCoeffArray;
  using NeighborhoodPixelArray = FILTER_UTILS::ZOOM_FILTER_COEFFS::NeighborhoodPixelArray;

  [[nodiscard]] auto GetNewColor(
      const ZoomFilterBuffers::SourcePointInfo& sourcePointInfo,
      const std::array<Pixel, PixelBuffer::NUM_NBRS>& sourcePointNeighbours) const noexcept
      -> Pixel;

  [[nodiscard]] auto GetNameValueParams(const std::string& paramGroup) const noexcept
      -> UTILS::NameValuePairs;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;
  bool m_blockyWavy = false;
  FXBuffSettings m_buffSettings{};

  static constexpr auto ALLOWED_NUM_NEIGHBORS = 4U;
  static_assert(ALLOWED_NUM_NEIGHBORS == FILTER_UTILS::ZOOM_FILTER_COEFFS::NUM_NEIGHBOR_COEFFS);
  std::array<uint32_t, ALLOWED_NUM_NEIGHBORS> m_reorderedColorIndexes{0, 1, 2, 3};

  libdivide::divider<uint32_t> m_coeffsAndBrightnessFastDivisor{FILTER_UTILS::ZOOM_FILTER_COEFFS::MAX_SUM_COEFFS};

  [[nodiscard]] auto GetFilteredColor(const NeighborhoodCoeffArray& coeffs,
                                      const NeighborhoodPixelArray& pixels) const noexcept -> Pixel;
  [[nodiscard]] auto GetMixedColor(const NeighborhoodCoeffArray& coeffs,
                                   const NeighborhoodPixelArray& colors) const noexcept -> Pixel;
  [[nodiscard]] auto GetBlockyMixedColor(const NeighborhoodCoeffArray& coeffs,
                                         const NeighborhoodPixelArray& colors) const noexcept
      -> Pixel;
};

inline FilterColorsService::FilterColorsService(const UTILS::MATH::IGoomRand& goomRand) noexcept
  : m_goomRand{goomRand}
{
}

inline auto FilterColorsService::SetBrightness(const float brightness) noexcept -> void
{
  // In method 'GetMixedColor' we multiply an array of coefficients by an array of colors
  // and get a sum as the result. The sum is then divided by 'MAX_SUM_COEFFS'. For optimizing
  // reasons, we can use this step to also factor in integer brightness for free.
  //
  //  (c/x) * (m/n) = (c*m) / (x*n) = c / (x*n / m)

  static constexpr auto X = FILTER_UTILS::ZOOM_FILTER_COEFFS::MAX_SUM_COEFFS;
  static constexpr auto N = channel_limits<uint32_t>::max();
  const auto m = std::max(1U, static_cast<uint32_t>(brightness * channel_limits<float>::max()));

  m_coeffsAndBrightnessFastDivisor = libdivide::divider<uint32_t>{(X * N) / m};
}

inline auto FilterColorsService::SetBlockyWavy(const bool val) noexcept -> void
{
  m_blockyWavy = val;

  if (m_blockyWavy)
  {
    m_goomRand.Shuffle(begin(m_reorderedColorIndexes), end(m_reorderedColorIndexes));
  }
}

inline void FilterColorsService::SetBuffSettings(const FXBuffSettings& settings) noexcept
{
  m_buffSettings = settings;
}

inline auto FilterColorsService::GetNewColor(
    const ZoomFilterBuffers::SourcePointInfo& sourcePointInfo,
    const std::array<Pixel, PixelBuffer::NUM_NBRS>& sourcePointNeighbours) const noexcept -> Pixel
{
  return GetFilteredColor(*sourcePointInfo.coeffs, sourcePointNeighbours);
}

inline auto FilterColorsService::GetFilteredColor(
    const NeighborhoodCoeffArray& coeffs, const NeighborhoodPixelArray& pixels) const noexcept
    -> Pixel
{
  if (m_blockyWavy)
  {
    return GetBlockyMixedColor(coeffs, pixels);
  }

  return GetMixedColor(coeffs, pixels);
}

inline auto FilterColorsService::GetBlockyMixedColor(
    const NeighborhoodCoeffArray& coeffs, const NeighborhoodPixelArray& colors) const noexcept
    -> Pixel
{
  // Changing the color order gives a strange blocky, wavy look when zooming in.

  const auto reorderedColors = NeighborhoodPixelArray{colors[m_reorderedColorIndexes[0]],
                                                      colors[m_reorderedColorIndexes[1]],
                                                      colors[m_reorderedColorIndexes[2]],
                                                      colors[m_reorderedColorIndexes[3]]};

  return GetMixedColor(coeffs, reorderedColors);
}

inline auto FilterColorsService::GetMixedColor(const NeighborhoodCoeffArray& coeffs,
                                               const NeighborhoodPixelArray& colors) const noexcept
    -> Pixel
{
  auto multR = 0U;
  auto multG = 0U;
  auto multB = 0U;
  for (auto i = 0U; i < FILTER_UTILS::ZOOM_FILTER_COEFFS::NUM_NEIGHBOR_COEFFS; ++i)
  {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    const auto coeff = coeffs[i];
    const auto color = colors[i];
    multR += static_cast<uint32_t>(color.R()) * coeff;
    multG += static_cast<uint32_t>(color.G()) * coeff;
    multB += static_cast<uint32_t>(color.B()) * coeff;
  }

  const auto newR = static_cast<PixelChannelType>(multR / m_coeffsAndBrightnessFastDivisor);
  const auto newG = static_cast<PixelChannelType>(multG / m_coeffsAndBrightnessFastDivisor);
  const auto newB = static_cast<PixelChannelType>(multB / m_coeffsAndBrightnessFastDivisor);

  return Pixel{
      Pixel::RGB{newR, newG, newB, MAX_ALPHA}
  };
}

} // namespace GOOM::FILTER_FX
