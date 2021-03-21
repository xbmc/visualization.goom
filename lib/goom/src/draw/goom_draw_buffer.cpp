#include "goom_draw_buffer.h"

#include "draw_methods.h"
#include "goom_graphic.h"

#undef NDEBUG
#include <cassert>
#include <cstdint>
#include <vector>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace DRAW
{
#else
namespace GOOM::DRAW
{
#endif

using UTILS::GetBrighterColorInt;
using UTILS::GetColorAdd;

GoomDrawBuffer::GoomDrawBuffer(const uint32_t screenWidth, const uint32_t screenHeight)
  : IGoomDraw{screenWidth, screenHeight,
              [&](int32_t x,
                  int32_t y,
                  const std::vector<Pixel>& newColors,
                  const bool allowOverexposed) {
                DrawPixels(m_multipleBuffers, x, y, newColors, GetIntBuffIntensity(),
                           allowOverexposed);
              }}
{
}

GoomDrawBuffer::~GoomDrawBuffer() noexcept = default;

auto GoomDrawBuffer::GetPixel(const int32_t x, const int32_t y) const -> Pixel
{
  assert(!m_multipleBuffers.empty());
  assert(m_multipleBuffers[0] != nullptr);
  return (*m_multipleBuffers[0])(static_cast<size_t>(x), static_cast<size_t>(y));
}

void GoomDrawBuffer::DrawPixelsUnblended(const int32_t x,
                                         const int32_t y,
                                         const std::vector<Pixel>& colors) const
{
  for (size_t i = 0; i < m_multipleBuffers.size(); i++)
  {
    (*m_multipleBuffers[i])(static_cast<size_t>(x), static_cast<size_t>(y)) = colors[i];
  }
}

void GoomDrawBuffer::DrawPixels(const std::vector<PixelBuffer*>& buffs,
                                const int32_t x,
                                const int32_t y,
                                const std::vector<Pixel>& colors,
                                const uint32_t intBuffIntensity,
                                const bool allowOverexposed)
{
  for (size_t i = 0; i < colors.size(); i++)
  {
    const Pixel newColor = GetBrighterColorInt(intBuffIntensity, colors[i], allowOverexposed);

    Pixel& p = (*buffs[i])(static_cast<size_t>(x), static_cast<size_t>(y));
    p = GetColorAdd(p, newColor, allowOverexposed);

    /***
      ATTEMPT AT BLENDING - WON'T WORK THOUGH - BECAUSE OF MULTIPLE BUFFERS??
        Pixel* const p = &(buffs[i][pos]);
        const Pixel existingColorBlended =
            GetBrighterColorInt(intBuffIntensity, *p, allowOverexposed);
        const Pixel pixColorBlended =
            GetBrighterColorInt(channel_limits<uint32_t>::max() - intBuffIntensity, newColors[i],
                                allowOverexposed);
        *p = GetColorAdd(existingColorBlended, pixColorBlended, allowOverexposed);
      ***/
  }
}

#if __cplusplus <= 201402L
} // namespace DRAW
} // namespace GOOM
#else
} // namespace GOOM::DRAW
#endif
