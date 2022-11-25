#include "goom_draw.h"

#include "utils/graphics/image_bitmaps.h"

#include <cstdint>

namespace GOOM::DRAW
{

using UTILS::GRAPHICS::ImageBitmap;

IGoomDraw::IGoomDraw(const Dimensions& dimensions) noexcept
  : m_dimensions{dimensions},
    m_drawMethods{m_dimensions,
                  [this](const int32_t x, const int32_t y, const MultiplePixels& newColors) {
                    DrawPixelsToDevice({x, y}, newColors);
                  }}
{
  SetBuffIntensity(m_buffIntensity);
  SetDefaultBlendPixelFunc();
}

inline auto IGoomDraw::DrawPixelsToDevice(const Point2dInt point,
                                          const MultiplePixels& colors) noexcept -> void
{
  DrawPixelsToDevice(point, colors, GetIntBuffIntensity());
}

auto IGoomDraw::Bitmap(const Point2dInt centre,
                       const ImageBitmap& bitmap,
                       const std::vector<GetBitmapColorFunc>& getColors) noexcept -> void
{
  const auto bitmapWidth  = bitmap.GetIntWidth();
  const auto bitmapHeight = bitmap.GetIntHeight();

  auto x0 = centre.x - (bitmapWidth / 2);
  auto y0 = centre.y - (bitmapHeight / 2);
  auto x1 = x0 + (bitmapWidth - 1);
  auto y1 = y0 + (bitmapHeight - 1);

  if ((x0 >= m_dimensions.GetIntWidth()) or (y0 >= m_dimensions.GetIntHeight()) or (x1 < 0) or
      (y1 < 0))
  {
    return;
  }
  if (x0 < 0)
  {
    x0 = 0;
  }
  if (y0 < 0)
  {
    y0 = 0;
  }
  if (x1 >= m_dimensions.GetIntWidth())
  {
    x1 = m_dimensions.GetIntWidth() - 1;
  }
  if (y1 >= m_dimensions.GetIntHeight())
  {
    y1 = m_dimensions.GetIntHeight() - 1;
  }

  const auto actualBitmapWidth  = static_cast<uint32_t>(x1 - x0) + 1;
  const auto actualBitmapHeight = static_cast<uint32_t>(y1 - y0) + 1;

  const auto setDestPixelRow =
      [this, &x0, &y0, &actualBitmapWidth, &bitmap, &getColors](const size_t bitmapY)
  {
    const auto numColors = getColors.size();
    const int buffY      = y0 + static_cast<int>(bitmapY);
    auto finalColors     = MultiplePixels(numColors);
    for (auto bitmapX = 0U; bitmapX < actualBitmapWidth; ++bitmapX)
    {
      const auto bitmapColor = bitmap(bitmapX, bitmapY);
      if ((0 == bitmapColor.A()) || (bitmapColor.IsBlack()))
      {
        continue;
      }
      for (auto i = 0U; i < numColors; ++i)
      {
        finalColors[i] = getColors[i](bitmapX, bitmapY, bitmapColor);
      }
      const auto buffX = x0 + static_cast<int>(bitmapX);
      DrawPixels({buffX, buffY}, finalColors);
    }
  };

  if (static constexpr auto MIN_PARALLEL_BITMAP_WIDTH = 200;
      bitmapWidth >= MIN_PARALLEL_BITMAP_WIDTH)
  {
    GetParallel().ForLoop(actualBitmapHeight, setDestPixelRow);
  }
  else
  {
    for (auto yBitmap = 0U; yBitmap < actualBitmapHeight; ++yBitmap)
    {
      setDestPixelRow(yBitmap);
    }
  }
}

} // namespace GOOM::DRAW
