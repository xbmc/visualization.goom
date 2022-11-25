#include "filter_buffer_color_info.h"

#include "color/color_utils.h"
#include "goom_config.h"

namespace GOOM::FILTER_FX
{

using COLOR::LUMA_BLUE_COMPONENT;
using COLOR::LUMA_GREEN_COMPONENT;
using COLOR::LUMA_RED_COMPONENT;

auto FilterBufferColorInfo::GetRegionInfoArray(
    const std::array<uint32_t, NUM_Y_REGIONS>& yRegionBorders) noexcept
    -> std::array<RegionInfo, NUM_REGIONS>
{
  auto regionRectArray = std::array<RegionInfo, NUM_REGIONS>{};

  auto regionIndex = 0U;
  auto y0          = 0U;
  for (const auto& yBorder : yRegionBorders)
  {
    const auto y1 = yBorder;
    assert(y0 <= y1);

    for (auto xRegionIndex = 0U; xRegionIndex < NUM_X_REGIONS; ++xRegionIndex)
    {
      regionRectArray.at(regionIndex) = {y0, y1, xRegionIndex};
      ++regionIndex;
    }

    y0 = y1 + 1;
  }

  Ensures(regionIndex == NUM_REGIONS);

  return regionRectArray;
}

auto FilterBufferColorInfo::GetFilterBufferRowColorInfoArray(
    const uint32_t height, const std::array<uint32_t, NUM_X_REGIONS>& xRegionBorders) noexcept
    -> std::vector<FilterBufferRowColorInfo>
{
  auto filterBufferRowColorInfo = std::vector<FilterBufferRowColorInfo>{};
  filterBufferRowColorInfo.reserve(height);

  for (auto y = 0U; y < height; ++y)
  {
    filterBufferRowColorInfo.emplace_back(xRegionBorders);
  }

  return filterBufferRowColorInfo;
}

inline auto FilterBufferColorInfo::FilterBufferRowColorInfo::GetXRegionCounts(
    const size_t xRegionIndex) const noexcept -> Counts
{
  return m_xRegionCountsArray.at(xRegionIndex);
}

inline auto FilterBufferColorInfo::GetAverageLuminance(const Counts& totals) noexcept -> float
{
  if (0 == totals.numNonzeroInRow)
  {
    return 0.0F;
  }

  return ((LUMA_RED_COMPONENT * static_cast<float>(totals.sumRedInRow)) +
          (LUMA_GREEN_COMPONENT * static_cast<float>(totals.sumGreenInRow)) +
          (LUMA_BLUE_COMPONENT * static_cast<float>(totals.sumBlueInRow))) /
         (static_cast<float>(totals.numNonzeroInRow) * channel_limits<float>::max());
}

auto FilterBufferColorInfo::CalculateLuminances() noexcept -> void
{
  for (auto i = 0U; i < NUM_REGIONS; ++i)
  {
    m_regionAverageLuminances.at(i) = GetRegionAverageLuminance(i);
  }
}

auto FilterBufferColorInfo::GetRegionAverageLuminance(const size_t regionIndex) const noexcept
    -> float
{
  const auto& regionInfo = m_regionInfoArray.at(regionIndex);

  auto totals = Counts{};

  for (auto y = regionInfo.y0; y <= regionInfo.y1; ++y)
  {
    const Counts& xRegionCounts =
        m_filterBufferRowColorInfoArray.at(y).GetXRegionCounts(regionInfo.xRegionIndex);

    totals.numNonzeroInRow += xRegionCounts.numNonzeroInRow;
    totals.sumRedInRow += xRegionCounts.sumRedInRow;
    totals.sumGreenInRow += xRegionCounts.sumGreenInRow;
    totals.sumBlueInRow += xRegionCounts.sumBlueInRow;
  }

  return GetAverageLuminance(totals);
}

auto FilterBufferColorInfo::GetMaxRegionAverageLuminance() const noexcept -> float
{
  auto maxAverageLuminance = 0.0F;
  for (const auto regionAverageLuminance : m_regionAverageLuminances)
  {
    if (regionAverageLuminance > maxAverageLuminance)
    {
      maxAverageLuminance = regionAverageLuminance;
    }
  }

  return maxAverageLuminance;
}

auto FilterBufferColorInfo::GetRegionAverageLuminanceAtPoint(const Point2dInt& point) const noexcept
    -> float
{
  return m_regionAverageLuminances.at(GetRegionIndexOfPoint(point));
}

inline auto FilterBufferColorInfo::GetRegionIndexOfPoint(const Point2dInt& point) const noexcept
    -> size_t
{
  for (auto regionIndex = 0U; regionIndex < NUM_REGIONS; ++regionIndex)
  {
    const auto& regionInfo = m_regionInfoArray.at(regionIndex);
    const auto y0          = static_cast<int32_t>(regionInfo.y0);
    const auto y1          = static_cast<int32_t>(regionInfo.y1);

    if ((y0 <= point.y) && (point.y <= y1) && IsInXRegion(point.x, regionInfo.xRegionIndex))
    {
      return regionIndex;
    }
  }

  FailFast();
  return 0;
}

inline auto FilterBufferColorInfo::IsInXRegion(const int32_t x,
                                               const size_t xRegionIndex) const noexcept -> bool
{
  const auto x0 =
      0 == xRegionIndex ? 0 : static_cast<int32_t>(m_xRegionBorders.at(xRegionIndex - 1));
  const auto x1 = static_cast<int32_t>(m_xRegionBorders.at(xRegionIndex));

  return (x0 <= x) && (x <= x1);
}

auto FilterBufferColorInfo::GetAverageLuminanceTest() const noexcept -> float
{
  auto totals = Counts{};

  for (const auto& filterBufferRowColorInfo : m_filterBufferRowColorInfoArray)
  {
    const auto regionTotals = filterBufferRowColorInfo.GetXRegionTotals();

    totals.numNonzeroInRow += regionTotals.numNonzeroInRow;
    totals.sumRedInRow += regionTotals.sumRedInRow;
    totals.sumGreenInRow += regionTotals.sumGreenInRow;
    totals.sumBlueInRow += regionTotals.sumBlueInRow;
  }

  return GetAverageLuminance(totals);
}

auto FilterBufferColorInfo::FilterBufferRowColorInfo::GetXRegionTotals() const noexcept -> Counts
{
  auto totals = Counts{};
  for (const auto& regionCounts : m_xRegionCountsArray)
  {
    totals.numNonzeroInRow += regionCounts.numNonzeroInRow;
    totals.sumRedInRow += regionCounts.sumRedInRow;
    totals.sumGreenInRow += regionCounts.sumGreenInRow;
    totals.sumBlueInRow += regionCounts.sumBlueInRow;
  }

  return totals;
}

} // namespace GOOM::FILTER_FX
