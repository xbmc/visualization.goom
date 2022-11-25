#include "color_utils.h"

#include "goom_graphic.h"

#include <cmath>

namespace GOOM::COLOR
{

inline auto Lighten(const PixelChannelType value, const float power) -> PixelChannelType
{
  const auto t = (static_cast<float>(value) * std::log10(power)) / 2.0F;
  if (t <= 0.0F)
  {
    return 0;
  }

  // (32.0f * log (t));
  return static_cast<PixelChannelType>(
      std::clamp(static_cast<int>(t), channel_limits<int>::min(), channel_limits<int>::max()));
}

auto GetLightenedColor(const Pixel& oldColor, const float power) -> Pixel
{
  auto pixel = oldColor;

  pixel.SetR(Lighten(pixel.R(), power));
  pixel.SetG(Lighten(pixel.G(), power));
  pixel.SetB(Lighten(pixel.B(), power));

  return pixel;
}

[[nodiscard]] inline auto EvolvedColor(const Pixel& src,
                                       const Pixel& dest,
                                       const PixelIntType mask,
                                       const PixelIntType incr) -> Pixel
{
  struct RGBChannels
  {
    PixelChannelType r;
    PixelChannelType g;
    PixelChannelType b;
    PixelChannelType a;
  };
  union RGBColor
  {
    RGBChannels channels;
    PixelIntType intVal;
  };

  const auto srcColor = RGBColor{
      {src.R(), src.G(), src.B(), src.A()}
  };
  auto iMaskedSrc = srcColor.intVal & mask; // NOLINT: union hard to fix here

  const auto destColor = RGBColor{
      {dest.R(), dest.G(), dest.B(), dest.A()}
  };
  const auto iMaskedDest = destColor.intVal & mask; // NOLINT: union hard to fix here

  if ((iMaskedSrc != mask) && (iMaskedSrc < iMaskedDest))
  {
    iMaskedSrc += incr;
  }
  if (iMaskedSrc > iMaskedDest)
  {
    iMaskedSrc -= incr;
  }

  const auto color = srcColor.intVal & (~mask); // NOLINT: union hard to fix here

  RGBColor finalColor;
  finalColor.intVal = (iMaskedSrc & mask) | color; // NOLINT: union hard to fix here

  return Pixel{
  // NOLINTNEXTLINE: union hard to fix here
      {finalColor.channels.r, finalColor.channels.g, finalColor.channels.b, finalColor.channels.a}
  };
}

auto GetEvolvedColor(const Pixel& baseColor) -> Pixel
{
  auto newColor = baseColor;

  newColor = EvolvedColor(newColor, baseColor, 0xFFU, 0x01U);
  newColor = EvolvedColor(newColor, baseColor, 0xFF00U, 0x0100U);
  newColor = EvolvedColor(newColor, baseColor, 0xFF0000U, 0x010000U);
  newColor = EvolvedColor(newColor, baseColor, 0xFF000000U, 0x01000000U);

  static constexpr auto LIGHTENED_COLOR_POWER = (10.0F * 2.0F) + 2.0F;
  newColor                                    = GetLightenedColor(newColor, LIGHTENED_COLOR_POWER);

  return newColor;
}

} // namespace GOOM::COLOR
