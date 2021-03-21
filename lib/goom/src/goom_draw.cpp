#include "goom_draw.h"

#include <cstdint>

namespace GOOM
{

using namespace UTILS;

IGoomDraw::IGoomDraw(const uint32_t screenWidth,
                     const uint32_t screenHeight,
                     const DrawMethods::DrawPixelFunc& drawPixelFunc)
  : m_screenWidth{screenWidth},
    m_screenHeight{screenHeight},
    m_drawMethods{m_screenWidth, m_screenHeight, drawPixelFunc},
    m_intBuffIntensity{},
    m_parallel{-1} // max cores - 1
{
  SetBuffIntensity(m_buffIntensity);
}

IGoomDraw::~IGoomDraw() noexcept = default;

void IGoomDraw::Bitmap(const int xCentre,
                       const int yCentre,
                       const PixelBuffer& bitmap,
                       const std::vector<GetBitmapColorFunc>& getColors,
                       const bool allowOverexposed) const
{
  const auto bitmapWidth = static_cast<int>(bitmap.GetWidth());
  const auto bitmapHeight = static_cast<int>(bitmap.GetHeight());

  int x0 = xCentre - bitmapWidth / 2;
  int y0 = yCentre - bitmapHeight / 2;
  int x1 = x0 + bitmapWidth - 1;
  int y1 = y0 + bitmapHeight - 1;

  if (x0 >= static_cast<int>(GetScreenWidth()) || y0 >= static_cast<int>(GetScreenHeight()) ||
      x1 < 0 || y1 < 0)
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
  if (x1 >= static_cast<int>(GetScreenWidth()))
  {
    x1 = static_cast<int>(GetScreenWidth() - 1);
  }
  if (y1 >= static_cast<int>(GetScreenHeight()))
  {
    y1 = static_cast<int>(GetScreenHeight() - 1);
  }

  const size_t actualBitmapWidth = static_cast<size_t>(x1 - x0) + 1;
  const size_t actualBitmapHeight = static_cast<size_t>(y1 - y0) + 1;

  const auto setDestPixelRow = [&](const size_t yBitmap) {
    const int yBuff = y0 + static_cast<int>(yBitmap);
    for (size_t xBitmap = 0; xBitmap < actualBitmapWidth; xBitmap++)
    {
      const Pixel bitmapColor = bitmap(xBitmap, yBitmap);
      if (bitmapColor.A() == 0 || bitmapColor == Pixel::BLACK)
      {
        continue;
      }
      std::vector<Pixel> finalColors(getColors.size());
      for (size_t i = 0; i < getColors.size(); i++)
      {
        finalColors[i] = getColors[i](xBitmap, yBitmap, bitmapColor);
      }
      const int xBuff = x0 + static_cast<int>(xBitmap);
      DrawPixels(xBuff, yBuff, finalColors, allowOverexposed);
    }
  };

  if (bitmapWidth > 199)
  {
    GetParallel().ForLoop(actualBitmapHeight, setDestPixelRow);
  }
  else
  {
    for (size_t yBitmap = 0; yBitmap < actualBitmapHeight; yBitmap++)
    {
      setDestPixelRow(yBitmap);
    }
  }
}

} // namespace GOOM
