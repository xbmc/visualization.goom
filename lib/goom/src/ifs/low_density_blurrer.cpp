#include "low_density_blurrer.h"

#include "colorizer.h"
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

using UTILS::GetBrighterColor;
using UTILS::GetColorAverage;
using UTILS::IColorMap;

LowDensityBlurrer::LowDensityBlurrer(const IGoomDraw* const draw,
                                     const uint32_t width,
                                     const Colorizer* colorizer) noexcept
  : m_draw{draw}, m_width{width}, m_colorizer{colorizer}
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
    if (p.GetX() < (m_width / 2) || p.GetY() < (m_width / 2) ||
        p.GetX() >= m_draw->GetScreenWidth() - (m_width / 2) ||
        p.GetY() >= m_draw->GetScreenHeight() - (m_width / 2))
    {
      p.SetCount(0); // just signal that no need to set buff
      continue;
    }

    size_t n = 0;
    auto neighY = static_cast<int32_t>(p.GetY() - m_width / 2);
    for (size_t i = 0; i < m_width; i++)
    {
      auto neighX = static_cast<int32_t>(p.GetX() - m_width / 2);
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
    if (p.GetCount() == 0)
    {
      continue;
    }
    const std::vector<Pixel> colors{p.GetColor(), p.GetColor()};
    // TODO bitmap here
    m_draw->DrawPixels(static_cast<int32_t>(p.GetX()), static_cast<int32_t>(p.GetY()), colors);
    // ??? NOTE: We need to set raw (unblended) pixels here, otherwise we get unpleasant overexposure.
    //m_draw->DrawPixelsUnblended(static_cast<int32_t>(p.x), static_cast<int32_t>(p.y), colors);
  }
}

void LowDensityBlurrer::SetPointColor(IfsPoint& point,
                                      const float t,
                                      const float logMaxLowDensityCount,
                                      const std::vector<Pixel>& neighbours) const
{
  const float logAlpha = point.GetCount() <= 1 ? 1.0F
                                               : std::log(static_cast<float>(point.GetCount())) /
                                                     logMaxLowDensityCount;
  constexpr float BRIGHTNESS = 0.5F;

  switch (m_colorMode)
  {
    case BlurrerColorMode::SINGLE_NO_NEIGHBOURS:
      point.SetColor(m_singleColor);
      break;
    case BlurrerColorMode::SINGLE_WITH_NEIGHBOURS:
      point.SetColor(
          IColorMap::GetColorMix(m_singleColor, GetColorAverage(neighbours), m_neighbourMixFactor));
      break;
    case BlurrerColorMode::SIMI_NO_NEIGHBOURS:
      point.SetColor(point.GetSimiColor());
      break;
    case BlurrerColorMode::SIMI_WITH_NEIGHBOURS:
    {
      const float fx =
          static_cast<float>(point.GetX()) / static_cast<float>(m_draw->GetScreenWidth());
      const float fy =
          static_cast<float>(point.GetY()) / static_cast<float>(m_draw->GetScreenHeight());
      point.SetColor(m_colorizer->GetMixedColor(IColorMap::GetColorMix(point.GetSimiColor(),
                                                                       GetColorAverage(neighbours),
                                                                       m_neighbourMixFactor),
                                                point.GetCount(), BRIGHTNESS, logAlpha, fx, fy));
      break;
    }
    case BlurrerColorMode::SMOOTH_NO_NEIGHBOURS:
      point.SetColor(point.GetSimiColorMap()->GetColor(t));
      break;
    case BlurrerColorMode::SMOOTH_WITH_NEIGHBOURS:
    {
      const float fx =
          static_cast<float>(point.GetX()) / static_cast<float>(m_draw->GetScreenWidth());
      const float fy =
          static_cast<float>(point.GetY()) / static_cast<float>(m_draw->GetScreenHeight());
      point.SetColor(m_colorizer->GetMixedColor(
          IColorMap::GetColorMix(point.GetSimiColorMap()->GetColor(t), GetColorAverage(neighbours),
                                 m_neighbourMixFactor),
          point.GetCount(), BRIGHTNESS, logAlpha, fx, fy));
      break;
    }
  }

  point.SetColor(GetGammaCorrection(BRIGHTNESS * logAlpha, point.GetColor()));
}

inline auto LowDensityBlurrer::GetGammaCorrection(const float brightness, const Pixel& color) const
    -> Pixel
{
  // if constexpr (GAMMA == 1.0F)
  if (GAMMA == 1.0F)
  {
    return GetBrighterColor(brightness, color, true);
  }
  return m_gammaCorrect.GetCorrection(brightness, color);
}

#if __cplusplus <= 201402L
} // namespace IFS
} // namespace GOOM
#else
} // namespace GOOM::IFS
#endif
