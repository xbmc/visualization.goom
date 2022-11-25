#include "goom_draw_to_container.h"

//#undef NO_LOGGING

#include "color/color_utils.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "goom_types.h"
#include "logging.h"

#include <cstdint>
#include <vector>

namespace GOOM::DRAW
{

using COLOR::GetBrighterColorInt;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)

GoomDrawToContainer::GoomDrawToContainer(const Dimensions& dimensions) noexcept
  : IGoomDraw{dimensions}, m_xyPixelList(dimensions.GetHeight())
{
  for (auto& xPixelList : m_xyPixelList)
  {
    xPixelList.resize(dimensions.GetWidth());
  }
}

GoomDrawToContainer::~GoomDrawToContainer() noexcept = default;

auto GoomDrawToContainer::ClearAll() noexcept -> void
{
  m_orderedXYPixelList.clear();

  for (auto& xPixelList : m_xyPixelList)
  {
    for (auto& colorsList : xPixelList)
    {
      colorsList.count = 0;
    }
  }
}

inline auto GoomDrawToContainer::GetWriteableColorsList(const Point2dInt point) noexcept
    -> ColorsList&
{
  return m_xyPixelList.at(static_cast<size_t>(point.y)).at(static_cast<size_t>(point.x));
}

auto GoomDrawToContainer::DrawPixelsUnblended(
    [[maybe_unused]] const Point2dInt point, [[maybe_unused]] const MultiplePixels& colors) noexcept
    -> void
{
  FailFast();
}

auto GoomDrawToContainer::DrawPixelsToDevice(const Point2dInt point,
                                             const MultiplePixels& colors,
                                             const uint32_t intBuffIntensity) noexcept -> void
{
  auto& colorsList = GetWriteableColorsList(point);

  if (colorsList.count == colorsList.colorsArray.size())
  {
    return;
  }

  // NOTE: Just save the first pixel in 'colors'. May need to improve this.
  const auto newColor = GetBrighterColorInt(intBuffIntensity, colors[0]);

  colorsList.colorsArray[colorsList.count] = newColor;
  ++colorsList.count;
  if (1 == colorsList.count)
  {
    m_orderedXYPixelList.emplace_back(point);
  }
}

auto GoomDrawToContainer::ResizeChangedCoordsKeepingNewest(const size_t numToKeep) noexcept -> void
{
  Expects(numToKeep <= m_orderedXYPixelList.size());

  const auto eraseFrom = cbegin(m_orderedXYPixelList);
  const auto eraseTo   = cbegin(m_orderedXYPixelList) +
                       static_cast<std::ptrdiff_t>(m_orderedXYPixelList.size() - numToKeep);

  for (auto coords = eraseFrom; coords != eraseTo; ++coords)
  {
    GetWriteableColorsList(*coords).count = 0;
  }

  m_orderedXYPixelList.erase(eraseFrom, eraseTo);
  m_orderedXYPixelList.resize(numToKeep);
}

auto GoomDrawToContainer::IterateChangedCoordsNewToOld(const CoordsFunc& func) const noexcept
    -> void
{
  const auto runFunc = [&](const size_t i)
  {
    const auto& coords     = m_orderedXYPixelList[i];
    const auto& colorsList = GetColorsList(coords);
    func(coords, colorsList);
  };

  // Start with the newest coords added.
  const auto maxIndex = static_cast<int32_t>(m_orderedXYPixelList.size() - 1);
  for (auto i = maxIndex; i >= 0; --i)
  {
    runFunc(static_cast<size_t>(i));
  }
}

} // namespace GOOM::DRAW
