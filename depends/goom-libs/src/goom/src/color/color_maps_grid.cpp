#include "color_maps_grids.h"

//#undef NO_LOGGING

#include "goom_config.h"
#include "logging.h"
#include "utils/t_values.h"

#include <cmath>

namespace GOOM::COLOR
{

using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::TValue;

ColorMapsGrid::ColorMapsGrid(const std::vector<const IColorMap*>& horizontalColorMaps,
                             const UTILS::TValue& verticalT,
                             const std::vector<const IColorMap*>& verticalColorMaps,
                             const ColorMixingTFunc& colorMixingTFunc) noexcept
  : m_horizontalColorMaps{horizontalColorMaps},
    m_verticalColorMaps{verticalColorMaps},
    m_verticalT{&verticalT},
    m_colorMixingT{colorMixingTFunc}
{
}

ColorMapsGrid::~ColorMapsGrid() noexcept = default;

auto ColorMapsGrid::GetCurrentHorizontalLineColors() const -> std::vector<Pixel>
{
  auto nextColors = std::vector<Pixel>(m_width);

  const auto* horizontalColorMap = m_horizontalColorMaps.at(GetCurrentHorizontalLineIndex());
  auto horizontalT               = TValue{TValue::StepType::SINGLE_CYCLE, m_width};

  for (auto i = 0U; i < m_width; ++i)
  {
    const auto horizontalColor = horizontalColorMap->GetColor(horizontalT());
    const auto verticalColor   = m_verticalColorMaps.at(i)->GetColor((*m_verticalT)());
    const auto mixT            = m_colorMixingT(horizontalT(), (*m_verticalT)());
    nextColors.at(i)           = IColorMap::GetColorMix(horizontalColor, verticalColor, mixT);

    horizontalT.Increment();
  }

  return nextColors;
}

inline auto ColorMapsGrid::GetCurrentHorizontalLineIndex() const -> size_t
{
  Expects(m_maxHorizontalLineIndex >= 0.0F);
  Expects((*m_verticalT)() >= 0.0F);

  return static_cast<size_t>(std::lround((*m_verticalT)() * m_maxHorizontalLineIndex));
}

} // namespace GOOM::COLOR
