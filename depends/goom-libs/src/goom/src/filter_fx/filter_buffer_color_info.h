#pragma once

#include "color/color_utils.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "goom_types.h"
#include "point2d.h"
#include "utils/math/misc.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace GOOM::FILTER_FX
{

class FilterBufferColorInfo
{
public:
  static constexpr uint32_t NUM_X_REGIONS = 5;
  static constexpr uint32_t NUM_Y_REGIONS = 3;

  class FilterBufferRowColorInfo
  {
  public:
    explicit FilterBufferRowColorInfo(
        const std::array<uint32_t, NUM_X_REGIONS>& xRegionBorders) noexcept;

    auto Reset() noexcept -> void;
    auto UpdateColor(const Pixel& color) noexcept -> void;
    auto NextX() noexcept -> void;

  private:
    const std::array<uint32_t, NUM_X_REGIONS>& m_xRegionBorders;
    uint32_t m_currentX            = 0;
    uint32_t m_currentXRegionIndex = 0;

    struct Counts
    {
      uint32_t numNonzeroInRow = 0;
      uint32_t sumRedInRow     = 0;
      uint32_t sumGreenInRow   = 0;
      uint32_t sumBlueInRow    = 0;
    };
    std::array<Counts, NUM_X_REGIONS> m_xRegionCountsArray{};
    [[nodiscard]] auto GetXRegionTotals() const noexcept -> Counts;
    [[nodiscard]] auto GetXRegionCounts(size_t xRegionIndex) const noexcept -> Counts;

    friend class FilterBufferColorInfo;
  };

  explicit FilterBufferColorInfo(const Dimensions& dimensions) noexcept;

  [[nodiscard]] auto GetRow(size_t y) noexcept -> FilterBufferRowColorInfo&;
  auto CalculateLuminances() noexcept -> void;
  [[nodiscard]] auto GetMaxRegionAverageLuminance() const noexcept -> float;
  [[nodiscard]] auto GetRegionAverageLuminanceAtPoint(const Point2dInt& point) const noexcept
      -> float;

private:
  const Dimensions m_dimensions;

  const std::array<uint32_t, NUM_X_REGIONS> m_xRegionBorders{
      GetRegionBorders<NUM_X_REGIONS>(m_dimensions.GetWidth())};
  const std::array<uint32_t, NUM_Y_REGIONS> m_yRegionBorders{
      GetRegionBorders<NUM_Y_REGIONS>(m_dimensions.GetHeight())};
  template<uint32_t NumRegions>
  [[nodiscard]] static auto GetRegionBorders(uint32_t length) noexcept
      -> std::array<uint32_t, NumRegions>;

  std::vector<FilterBufferRowColorInfo> m_filterBufferRowColorInfoArray{
      GetFilterBufferRowColorInfoArray(m_dimensions.GetHeight(), m_xRegionBorders)};
  [[nodiscard]] static auto GetFilterBufferRowColorInfoArray(
      uint32_t height, const std::array<uint32_t, NUM_X_REGIONS>& xRegionBorders) noexcept
      -> std::vector<FilterBufferRowColorInfo>;

  static constexpr uint32_t NUM_REGIONS = NUM_X_REGIONS * NUM_Y_REGIONS;
  struct RegionInfo
  {
    uint32_t y0;
    uint32_t y1;
    uint32_t xRegionIndex;
  };
  const std::array<RegionInfo, NUM_REGIONS> m_regionInfoArray{GetRegionInfoArray(m_yRegionBorders)};
  [[nodiscard]] static auto GetRegionInfoArray(
      const std::array<uint32_t, NUM_Y_REGIONS>& yRegionBorders) noexcept
      -> std::array<RegionInfo, NUM_REGIONS>;
  [[nodiscard]] auto GetRegionIndexOfPoint(const Point2dInt& point) const noexcept -> size_t;
  [[nodiscard]] auto IsInXRegion(int32_t x, size_t xRegionIndex) const noexcept -> bool;

  std::array<float, NUM_REGIONS> m_regionAverageLuminances{};
  [[nodiscard]] auto GetRegionAverageLuminance(size_t regionIndex) const noexcept -> float;
  using Counts = FilterBufferRowColorInfo::Counts;
  [[nodiscard]] static auto GetAverageLuminance(const Counts& totals) noexcept -> float;

  [[nodiscard]] auto GetAverageLuminanceTest() const noexcept -> float;
};

inline FilterBufferColorInfo::FilterBufferColorInfo(const Dimensions& dimensions) noexcept
  : m_dimensions{dimensions}
{
  static_assert(UTILS::MATH::IsOdd(NUM_X_REGIONS));
  static_assert(UTILS::MATH::IsOdd(NUM_Y_REGIONS));
}

inline auto FilterBufferColorInfo::GetRow(const size_t y) noexcept -> FilterBufferRowColorInfo&
{
  return m_filterBufferRowColorInfoArray[y];
}

template<uint32_t NumRegions>
auto FilterBufferColorInfo::GetRegionBorders(const uint32_t length) noexcept
    -> std::array<uint32_t, NumRegions>
{
  Expects(length > 0);

  static_assert(NumRegions > 0);
  const auto regionSize = length / NumRegions;

  auto regionBorders = std::array<uint32_t, NumRegions>{};
  auto border        = regionSize - 1;
  for (auto& regionBorder : regionBorders)
  {
    regionBorder = border;

    border += regionSize;
    if (border >= length)
    {
      border = length - 1;
    }
    assert(border < length);
  }

  return regionBorders;
}

inline FilterBufferColorInfo::FilterBufferRowColorInfo::FilterBufferRowColorInfo(
    const std::array<uint32_t, NUM_X_REGIONS>& xRegionBorders) noexcept
  : m_xRegionBorders{xRegionBorders}
{
}

inline auto FilterBufferColorInfo::FilterBufferRowColorInfo::Reset() noexcept -> void
{
  m_currentX            = 0;
  m_currentXRegionIndex = 0;

  for (auto& regionCounts : m_xRegionCountsArray)
  {
    regionCounts.numNonzeroInRow = 0;
    regionCounts.sumRedInRow     = 0;
    regionCounts.sumGreenInRow   = 0;
    regionCounts.sumBlueInRow    = 0;
  }
}

inline auto FilterBufferColorInfo::FilterBufferRowColorInfo::UpdateColor(
    const Pixel& color) noexcept -> void
{
  if (COLOR::IsCloseToBlack(color))
  {
    return;
  }

  auto& regionCounts = m_xRegionCountsArray.at(m_currentXRegionIndex);
  ++regionCounts.numNonzeroInRow;
  regionCounts.sumRedInRow += color.R();
  regionCounts.sumGreenInRow += color.G();
  regionCounts.sumBlueInRow += color.B();
}

inline auto FilterBufferColorInfo::FilterBufferRowColorInfo::NextX() noexcept -> void
{
  ++m_currentX;
  if (m_currentX > m_xRegionBorders.at(m_currentXRegionIndex))
  {
    ++m_currentXRegionIndex;
  }
}

} // namespace GOOM::FILTER_FX
