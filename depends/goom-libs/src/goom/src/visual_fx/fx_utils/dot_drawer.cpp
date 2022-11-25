#include "dot_drawer.h"

#include "draw/goom_draw.h"
#include "point2d.h"
#include "utils/enum_utils.h"
#include "utils/graphics/image_bitmaps.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"

namespace GOOM::VISUAL_FX::FX_UTILS
{

using COLOR::GetColorMultiply;
using DRAW::IGoomDraw;
using DRAW::MultiplePixels;
using UTILS::NUM;
using UTILS::GRAPHICS::ImageBitmap;
using UTILS::GRAPHICS::SmallImageBitmaps;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::Weights;

DotDrawer::DotDrawer(DRAW::IGoomDraw& draw,
                     const IGoomRand& goomRand,
                     const SmallImageBitmaps& smallBitmaps,
                     const Weights<DotSizes>& minDotSizes,
                     const Weights<DotSizes>& normalDotSizes) noexcept
  : m_goomDraw{draw},
    m_goomRand{goomRand},
    m_smallBitmaps{smallBitmaps},
    m_minDotSizes{minDotSizes},
    m_normalDotSizes{normalDotSizes}
{
  static_assert(MAX_IMAGE_DOT_SIZE <= SmallImageBitmaps::MAX_IMAGE_SIZE, "Max dot size mismatch.");
}

auto DotDrawer::ChangeDotSizes() noexcept -> void
{
  static constexpr auto MAX_DOT_SIZE = 7U;
  static_assert(MAX_DOT_SIZE <= (MAX_IMAGE_DOT_SIZE - 1U));
  m_currentDotSize = GetNextDotSize(MAX_DOT_SIZE);

  static constexpr auto PROB_BEADED_LOOK = 0.15F;
  m_beadedLook                           = m_goomRand.ProbabilityOf(PROB_BEADED_LOOK);
  m_maxBeadedDotSize = m_goomRand.GetRandInRange(MAX_DOT_SIZE + 1, MAX_IMAGE_DOT_SIZE + 1);
}

auto DotDrawer::DrawDot(const DotSizes dotSize,
                        const Point2dInt& point,
                        const DRAW::MultiplePixels& colors,
                        const float brightness) noexcept -> void
{
  DrawDot(INT_DOT_SIZE[dotSize], point, colors, brightness);
}

auto DotDrawer::DrawDot(const Point2dInt& point,
                        const MultiplePixels& colors,
                        const float brightness) noexcept -> void
{
  const auto dotSize = not m_beadedLook ? m_currentDotSize : GetNextDotSize(m_maxBeadedDotSize);

  DrawDot(dotSize, point, colors, brightness);
}

inline auto DotDrawer::DrawDot(const uint32_t dotSize,
                               const Point2dInt& point,
                               const MultiplePixels& colors,
                               const float brightness) noexcept -> void
{
  if (dotSize <= 1)
  {
    return;
  }

  const auto getColor1 = [&brightness, &colors]([[maybe_unused]] const size_t x,
                                                [[maybe_unused]] const size_t y,
                                                const Pixel& bgnd)
  { return GetColorMultiply(bgnd, COLOR::GetBrighterColor(brightness, colors[0])); };

  const auto getColor2 = [&brightness, &colors]([[maybe_unused]] const size_t x,
                                                [[maybe_unused]] const size_t y,
                                                const Pixel& bgnd)
  { return GetColorMultiply(bgnd, COLOR::GetBrighterColor(brightness, colors[1])); };

  const auto getColors = std::vector<IGoomDraw::GetBitmapColorFunc>{getColor1, getColor2};
  const auto& bitmap   = GetImageBitmap(dotSize);

  m_goomDraw.Bitmap(point, bitmap, getColors);
}

auto DotDrawer::GetNextDotSize(const uint32_t maxSize) const noexcept -> uint32_t
{
  if (static constexpr auto MAX_MIN_DOT_SIZE = 7U; maxSize <= MAX_MIN_DOT_SIZE)
  {
    return INT_DOT_SIZE[m_minDotSizes.GetRandomWeighted()];
  }
  return INT_DOT_SIZE[m_normalDotSizes.GetRandomWeighted()];
}

inline auto DotDrawer::GetImageBitmap(const uint32_t size) const noexcept -> const ImageBitmap&
{
  return m_smallBitmaps.GetImageBitmap(SmallImageBitmaps::ImageNames::CIRCLE,
                                       std::clamp(size, MIN_IMAGE_DOT_SIZE, MAX_IMAGE_DOT_SIZE));
}

} // namespace GOOM::VISUAL_FX::FX_UTILS
