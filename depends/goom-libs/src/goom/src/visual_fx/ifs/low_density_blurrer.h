#pragma once

#include "color/color_adjustment.h"
#include "draw/goom_draw.h"
#include "goom_graphic.h"
#include "utils/math/misc.h"

#include <cstdint>
#include <vector>

namespace GOOM
{

namespace DRAW
{
class IGoomDraw;
}

namespace UTILS::GRAPHICS
{
class ImageBitmap;
class SmallImageBitmaps;
}
namespace UTILS::MATH
{
class IGoomRand;
}

namespace VISUAL_FX::IFS
{

class IfsPoint;
class Colorizer;

enum class BlurrerColorMode
{
  SMOOTH_WITH_NEIGHBOURS,
  SMOOTH_NO_NEIGHBOURS,
  SIMI_WITH_NEIGHBOURS,
  SIMI_NO_NEIGHBOURS,
  SINGLE_WITH_NEIGHBOURS,
  SINGLE_NO_NEIGHBOURS,
  _num // unused, and marks the enum end
};

class LowDensityBlurrer
{
public:
  LowDensityBlurrer() noexcept = delete;
  LowDensityBlurrer(DRAW::IGoomDraw& draw,
                    const UTILS::MATH::IGoomRand& goomRand,
                    uint32_t width,
                    const Colorizer* colorizer,
                    const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps) noexcept;

  [[nodiscard]] auto GetWidth() const noexcept -> uint32_t;
  auto SetWidth(uint32_t val) noexcept -> void;

  auto SetColorMode(BlurrerColorMode colorMode) noexcept -> void;
  auto SetSingleColor(const Pixel& color) noexcept -> void;

  auto SetNeighbourMixFactor(float neighbourMixFactor) noexcept -> void;

  auto DoBlur(std::vector<IfsPoint>& lowDensityPoints, uint32_t maxLowDensityCount) const noexcept
      -> void;

private:
  DRAW::IGoomDraw& m_draw;
  const UTILS::MATH::IGoomRand& m_goomRand;
  uint32_t m_width;
  size_t m_widthSquared = UTILS::MATH::Sq(static_cast<size_t>(m_width));
  const UTILS::GRAPHICS::SmallImageBitmaps& m_smallBitmaps;
  const UTILS::GRAPHICS::ImageBitmap* m_currentImageBitmap{};
  const Colorizer* const m_colorizer;
  float m_neighbourMixFactor = 1.0;
  BlurrerColorMode m_colorMode{};
  Pixel m_singleColor{};

  auto SetPointColors(std::vector<IfsPoint>& lowDensityPoints,
                      uint32_t maxLowDensityCount) const noexcept -> void;
  auto DrawPoints(const std::vector<IfsPoint>& lowDensityPoints) const noexcept -> void;
  auto DrawPoint(const IfsPoint& point) const noexcept -> void;
  [[nodiscard]] auto GetImageBitmap(bool useBitmaps) const noexcept
      -> const UTILS::GRAPHICS::ImageBitmap*;
  [[nodiscard]] auto GetBrightness() const noexcept -> float;
  [[nodiscard]] auto GetNeighbours(const IfsPoint& point) const noexcept -> std::vector<Pixel>;
  [[nodiscard]] auto GetPointColor(const IfsPoint& point,
                                   float t,
                                   const std::vector<Pixel>& neighbours,
                                   float logMaxLowDensityCount) const noexcept -> Pixel;
  [[nodiscard]] auto GetMixedPointColor(const Pixel& baseColor,
                                        const IfsPoint& point,
                                        const std::vector<Pixel>& neighbours,
                                        float brightness,
                                        float logAlpha) const noexcept -> Pixel;

  static constexpr float GAMMA = 2.2F;
  const COLOR::ColorAdjustment m_colorAdjust{GAMMA};
};

inline auto LowDensityBlurrer::GetWidth() const noexcept -> uint32_t
{
  return m_width;
}

inline auto LowDensityBlurrer::SetSingleColor(const Pixel& color) noexcept -> void
{
  m_singleColor = color;
}

inline auto LowDensityBlurrer::SetNeighbourMixFactor(const float neighbourMixFactor) noexcept
    -> void
{
  m_neighbourMixFactor = neighbourMixFactor;
}

} // namespace VISUAL_FX::IFS
} // namespace GOOM
