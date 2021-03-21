#include "low_density_blurrer.h"

#include "fractal.h"
#include "goom_draw.h"
#include "goom_graphic.h"
#include "goomutils/colormaps.h"

#include <cmath>
#include <cstdint>
#include <vector>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace IFS
{
#else
namespace GOOM::IFS
{
#endif

using UTILS::GetColorAverage;
using UTILS::IColorMap;

LowDensityBlurrer::LowDensityBlurrer(const IGoomDraw* const draw, const uint32_t width) noexcept
  : m_draw{draw}, m_width{width}
{
}

void LowDensityBlurrer::SetWidth(const uint32_t val)
{
  if (val != 3 && val != 5 && val != 7)
  {
    throw std::logic_error(std20::format("Invalid blur width {}.", val));
  }
  m_width = val;
}

void LowDensityBlurrer::DoBlur(std::vector<IfsPoint>& lowDensityPoints,
                               const uint32_t maxLowDensityCount) const
{
  std::vector<Pixel> neighbours(static_cast<size_t>(m_width) * static_cast<size_t>(m_width));
  const float logMaxLowDensityCount = std::log(static_cast<float>(maxLowDensityCount));

  float t = 0.0;
  const float tStep = 1.0F / static_cast<float>(lowDensityPoints.size());
  for (auto& p : lowDensityPoints)
  {
    if (p.x < (m_width / 2) || p.y < (m_width / 2) ||
        p.x >= m_draw->GetScreenWidth() - (m_width / 2) ||
        p.y >= m_draw->GetScreenHeight() - (m_width / 2))
    {
      p.count = 0; // just signal that no need to set buff
      continue;
    }

    size_t n = 0;
    auto neighY = static_cast<int32_t>(p.y - m_width / 2);
    for (size_t i = 0; i < m_width; i++)
    {
      auto neighX = static_cast<int32_t>(p.x - m_width / 2);
      for (size_t j = 0; j < m_width; j++)
      {
        neighbours[n] = m_draw->GetPixel(neighX, neighY);
        n++;
        neighX++;
      }
      neighY++;
    }

    SetPointColor(p, t, logMaxLowDensityCount, neighbours);

    t += tStep;
  }

  for (const auto& p : lowDensityPoints)
  {
    if (p.count == 0)
    {
      continue;
    }
    // NOTE: We need to set raw (unblended) pixels here, otherwise we get unpleasant overexposure.
    const std::vector<Pixel> colors{p.color, p.color};
    m_draw->DrawPixelsUnblended(static_cast<int32_t>(p.x), static_cast<int32_t>(p.y), colors);
  }
}

void LowDensityBlurrer::SetPointColor(IfsPoint& point,
                                      const float t,
                                      const float logMaxLowDensityCount,
                                      const std::vector<Pixel>& neighbours) const
{
  switch (m_colorMode)
  {
    case BlurrerColorMode::SINGLE_NO_NEIGHBOURS:
      point.color = m_singleColor;
      break;
    case BlurrerColorMode::SINGLE_WITH_NEIGHBOURS:
      point.color =
          IColorMap::GetColorMix(m_singleColor, GetColorAverage(neighbours), m_neighbourMixFactor);
      break;
    case BlurrerColorMode::SIMI_NO_NEIGHBOURS:
      point.color = point.simi->color;
      break;
    case BlurrerColorMode::SIMI_WITH_NEIGHBOURS:
      point.color = IColorMap::GetColorMix(point.simi->color, GetColorAverage(neighbours),
                                           m_neighbourMixFactor);
      break;
    case BlurrerColorMode::SMOOTH_NO_NEIGHBOURS:
      point.color = point.simi->colorMap->GetColor(t);
      break;
    case BlurrerColorMode::SMOOTH_WITH_NEIGHBOURS:
      point.color = IColorMap::GetColorMix(point.simi->colorMap->GetColor(t),
                                           GetColorAverage(neighbours), m_neighbourMixFactor);
      break;
  }

  const float logAlpha =
      point.count <= 1 ? 1.0F : std::log(static_cast<float>(point.count)) / logMaxLowDensityCount;
  constexpr float BRIGHTNESS = 1.0;
  point.color = m_blurGammaCorrect.GetCorrection(BRIGHTNESS * logAlpha, point.color);
}


#if __cplusplus <= 201402L
} // namespace IFS
} // namespace GOOM
#else
} // namespace GOOM::IFS
#endif
