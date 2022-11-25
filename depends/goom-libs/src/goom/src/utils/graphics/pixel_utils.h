#pragma once

#include "goom_graphic.h"
#include "utils/math/misc.h"

#include <cstdint>

namespace GOOM::UTILS::GRAPHICS
{

[[nodiscard]] constexpr auto MakePixel(uint32_t red,
                                       uint32_t green,
                                       uint32_t blue,
                                       uint32_t alpha) noexcept -> Pixel;

[[nodiscard]] constexpr auto MultiplyColorChannels(PixelChannelType ch1,
                                                   PixelChannelType ch2) noexcept -> uint32_t;
[[nodiscard]] constexpr auto MultiplyChannelColorByScalar(uint32_t scalar,
                                                          PixelChannelType channelVal) noexcept
    -> uint32_t;

constexpr auto MakePixel(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) noexcept
    -> Pixel
{
  if (red > MAX_CHANNEL_VALUE_HDR)
  {
    red = MAX_CHANNEL_VALUE_HDR;
  }
  if (green > MAX_CHANNEL_VALUE_HDR)
  {
    green = MAX_CHANNEL_VALUE_HDR;
  }
  if (blue > MAX_CHANNEL_VALUE_HDR)
  {
    blue = MAX_CHANNEL_VALUE_HDR;
  }
  if (alpha > MAX_ALPHA)
  {
    alpha = MAX_ALPHA;
  }

  return Pixel{static_cast<PixelChannelType>(red),
               static_cast<PixelChannelType>(green),
               static_cast<PixelChannelType>(blue),
               static_cast<PixelChannelType>(alpha)};
}

constexpr auto MultiplyColorChannels(const PixelChannelType ch1,
                                     const PixelChannelType ch2) noexcept -> uint32_t
{
  return (static_cast<uint32_t>(ch1) * static_cast<uint32_t>(ch2)) /
         channel_limits<uint32_t>::max();
}

static inline constexpr auto CHANNEL_COLOR_SCALAR_DIVISOR = channel_limits<uint32_t>::max() + 1U;

constexpr auto MultiplyChannelColorByScalar(const uint32_t scalar,
                                            const PixelChannelType channelVal) noexcept -> uint32_t
{
  constexpr auto CHANNEL_COLOR_SCALAR_DIVISOR_EXP = UTILS::MATH::Log2(CHANNEL_COLOR_SCALAR_DIVISOR);

  return (scalar * static_cast<uint32_t>(channelVal)) >> CHANNEL_COLOR_SCALAR_DIVISOR_EXP;
}

} // namespace GOOM::UTILS::GRAPHICS
