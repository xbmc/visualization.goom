#include "color_adjustment.h"

#include "color_utils.h"
#include "goom_config.h"
#include "utils/graphics/pixel_utils.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201) // glm: nonstandard extension used: nameless struct/union
#pragma warning(disable : 4242) // possible loss of data
#pragma warning(disable : 4244) // possible loss of data
#endif
#include <vivid/vivid.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

namespace GOOM::COLOR
{

using UTILS::GRAPHICS::MakePixel;
using UTILS::MATH::FloatsEqual;

auto ColorAdjustment::GetAdjustment(const float brightness, const Pixel& color) const -> Pixel
{
  Expects(brightness >= 0.0F);

  if (brightness < m_ignoreThreshold)
  {
    return GetBrighterColor(brightness, color);
  }

  auto adjustedColor = color;
  if (m_doAlterChroma)
  {
    adjustedColor = GetAlteredChromaColor(m_chromaFactor, adjustedColor);
  }

  if (not m_doAlterGamma)
  {
    return GetBrighterColor(brightness, adjustedColor);
  }

  const auto newR = static_cast<uint32_t>(std::round(
      channel_limits<float>::max() * std::pow(brightness * adjustedColor.RFlt(), m_gamma)));
  const auto newG = static_cast<uint32_t>(std::round(
      channel_limits<float>::max() * std::pow(brightness * adjustedColor.GFlt(), m_gamma)));
  const auto newB = static_cast<uint32_t>(std::round(
      channel_limits<float>::max() * std::pow(brightness * adjustedColor.BFlt(), m_gamma)));
  const auto newA = adjustedColor.A();

  return MakePixel(newR, newG, newB, newA);
}

auto ColorAdjustment::GetAlteredChromaColor(float lchYFactor, const Pixel& color) -> Pixel
{
  Expects(lchYFactor > 0.0F);

  if (FloatsEqual(1.0F, lchYFactor))
  {
    return color;
  }

  const auto rgb8 = vivid::col8_t{color.R(), color.G(), color.B()};
  auto lch        = vivid::lch::fromSrgb(vivid::rgb::fromRgb8(rgb8));

  static constexpr auto MAX_LCH_Y = 140.0F;
  lch.y = std::min(lch.y * lchYFactor, MAX_LCH_Y); // NOLINT: union hard to fix here

  const auto newRgb8 = vivid::rgb8::fromRgb(vivid::srgb::fromLch(lch));
  return Pixel{
      {newRgb8.r, newRgb8.g, newRgb8.b, MAX_ALPHA}  // NOLINT: union hard to fix here
  };
}

} // namespace GOOM::COLOR
