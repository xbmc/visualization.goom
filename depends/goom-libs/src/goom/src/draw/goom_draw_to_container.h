#pragma once

#include "goom_draw.h"
#include "goom_graphic.h"
#include "goom_types.h"
#include "point2d.h"

#include <array>
#include <cstdint>
#include <vector>

namespace GOOM::DRAW
{

class GoomDrawToContainer : public IGoomDraw
{
public:
  GoomDrawToContainer() noexcept = delete;
  explicit GoomDrawToContainer(const Dimensions& dimensions) noexcept;
  GoomDrawToContainer(const GoomDrawToContainer&) noexcept = delete;
  GoomDrawToContainer(GoomDrawToContainer&&) noexcept      = delete;
  ~GoomDrawToContainer() noexcept override;
  auto operator=(const GoomDrawToContainer&) noexcept -> GoomDrawToContainer& = delete;
  auto operator=(GoomDrawToContainer&&) noexcept -> GoomDrawToContainer&      = delete;

  [[nodiscard]] auto GetPixel(Point2dInt point) const noexcept -> Pixel override;
  auto DrawPixelsUnblended(Point2dInt point, const MultiplePixels& colors) noexcept
      -> void override;

  [[nodiscard]] auto GetPixels(Point2dInt point) const noexcept -> MultiplePixels;

  static constexpr size_t MAX_NUM_COLORS_LIST = 3;
  using ColorsArray                           = std::array<Pixel, MAX_NUM_COLORS_LIST>;
  struct ColorsList
  {
    uint8_t count = 0;
    ColorsArray colorsArray{};
  };
  [[nodiscard]] auto GetNumChangedCoords() const noexcept -> size_t;
  [[nodiscard]] auto GetChangedCoordsList() const noexcept -> const std::vector<Point2dInt>&;
  // IMPORTANT: The above is ordered from oldest to newest.
  [[nodiscard]] auto GetColorsList(Point2dInt point) const noexcept -> const ColorsList&;

  using CoordsFunc = std::function<void(Point2dInt point, const ColorsList& colorsList)>;
  // NOTE: 'func' must be thread-safe.
  auto IterateChangedCoordsNewToOld(const CoordsFunc& func) const noexcept -> void;

  auto ResizeChangedCoordsKeepingNewest(size_t numToKeep) noexcept -> void;
  auto ClearAll() noexcept -> void;

protected:
  auto DrawPixelsToDevice(Point2dInt point,
                          const MultiplePixels& colors,
                          uint32_t intBuffIntensity) noexcept -> void override;

private:
  std::vector<std::vector<ColorsList>> m_xyPixelList{};
  std::vector<Point2dInt> m_orderedXYPixelList{};
  [[nodiscard]] auto GetWriteableColorsList(Point2dInt point) noexcept -> ColorsList&;
  [[nodiscard]] auto GetLastDrawnColor(Point2dInt point) const noexcept -> Pixel;
  [[nodiscard]] auto GetLastDrawnColors(Point2dInt point) const noexcept -> MultiplePixels;
};

inline auto GoomDrawToContainer::GetPixel(const Point2dInt point) const noexcept -> Pixel
{
  return GetLastDrawnColor(point);
}

inline auto GoomDrawToContainer::GetPixels(const Point2dInt point) const noexcept -> MultiplePixels
{
  return GetLastDrawnColors(point);
}

inline auto GoomDrawToContainer::GetLastDrawnColor(const Point2dInt point) const noexcept -> Pixel
{
  const auto& colorsList = GetColorsList(point);
  if (0 == colorsList.count)
  {
    return BLACK_PIXEL;
  }
  return colorsList.colorsArray[static_cast<size_t>(colorsList.count - 1)];
}

inline auto GoomDrawToContainer::GetLastDrawnColors(const Point2dInt point) const noexcept
    -> MultiplePixels
{
  return {GetLastDrawnColor(point), BLACK_PIXEL};
}

inline auto GoomDrawToContainer::GetColorsList(const Point2dInt point) const noexcept
    -> const ColorsList&
{
  return m_xyPixelList.at(static_cast<size_t>(point.y)).at(static_cast<size_t>(point.x));
}

inline auto GoomDrawToContainer::GetNumChangedCoords() const noexcept -> size_t
{
  return m_orderedXYPixelList.size();
}

inline auto GoomDrawToContainer::GetChangedCoordsList() const noexcept
    -> const std::vector<Point2dInt>&
{
  return m_orderedXYPixelList;
}

} // namespace GOOM::DRAW
