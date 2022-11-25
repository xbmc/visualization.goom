#pragma once

#include "color_maps.h"
#include "goom_graphic.h"
#include "utils/t_values.h"

#include <cstdint>
#include <functional>
#include <vector>

namespace GOOM::COLOR
{

class ColorMapsGrid
{
public:
  using ColorMixingTFunc = std::function<float(float tX, float tY)>;

  ColorMapsGrid(const std::vector<const IColorMap*>& horizontalColorMaps,
                const UTILS::TValue& verticalT,
                const std::vector<const IColorMap*>& verticalColorMaps,
                const ColorMixingTFunc& colorMixingTFunc) noexcept;
  ColorMapsGrid(const ColorMapsGrid&) noexcept = delete;
  ColorMapsGrid(ColorMapsGrid&&) noexcept      = default;
  ~ColorMapsGrid() noexcept;
  auto operator=(const ColorMapsGrid&) noexcept = delete;
  auto operator=(ColorMapsGrid&&) noexcept      = delete;

  auto SetVerticalT(const UTILS::TValue& val) noexcept -> void;
  auto SetColorMaps(const std::vector<const IColorMap*>& horizontalColorMaps,
                    const std::vector<const IColorMap*>& verticalColorMaps) noexcept -> void;

  [[nodiscard]] auto GetCurrentHorizontalLineColors() const -> std::vector<Pixel>;

private:
  std::vector<const IColorMap*> m_horizontalColorMaps;
  float m_maxHorizontalLineIndex = static_cast<float>(m_horizontalColorMaps.size() - 1);
  std::vector<const IColorMap*> m_verticalColorMaps;
  uint32_t m_width = static_cast<uint32_t>(m_verticalColorMaps.size());

  const UTILS::TValue* m_verticalT;
  const ColorMixingTFunc m_colorMixingT;

  [[nodiscard]] auto GetCurrentHorizontalLineIndex() const -> size_t;
};

inline auto ColorMapsGrid::SetVerticalT(const UTILS::TValue& val) noexcept -> void
{
  m_verticalT = &val;
}

inline auto ColorMapsGrid::SetColorMaps(
    const std::vector<const IColorMap*>& horizontalColorMaps,
    const std::vector<const IColorMap*>& verticalColorMaps) noexcept -> void
{
  m_horizontalColorMaps    = horizontalColorMaps;
  m_maxHorizontalLineIndex = static_cast<float>(m_horizontalColorMaps.size() - 1);

  m_verticalColorMaps = verticalColorMaps;
  m_width             = static_cast<uint32_t>(m_verticalColorMaps.size());
}

} // namespace GOOM::COLOR
