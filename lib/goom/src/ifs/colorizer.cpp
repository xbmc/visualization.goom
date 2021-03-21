#include "colorizer.h"

#include "goomutils/colormaps.h"
#include "goomutils/goomrand.h"
#include "goomutils/random_colormaps.h"

#include <cmath>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace IFS
{
#else
namespace GOOM::IFS
{
#endif

using UTILS::GetRandInRange;
using UTILS::GetSlightlyDivergingStandardMaps;
using UTILS::IColorMap;
using UTILS::RandomColorMaps;
using UTILS::Weights;
using UTILS::COLOR_DATA::ColorMapName;

Colorizer::Colorizer() noexcept
{
  SetWeightedColorMaps(GetSlightlyDivergingStandardMaps());
}

inline void Colorizer::SetWeightedColorMaps(const std::shared_ptr<RandomColorMaps> weightedMaps)
{
  m_colorMaps = weightedMaps;

  m_mixerMap1Id = m_colorMapsManager.AddColorMapInfo(
      {m_colorMaps, ColorMapName::_NULL, RandomColorMaps::EMPTY});
  m_prevMixerMap1 = m_colorMapsManager.GetColorMapPtr(m_mixerMap1Id);
  m_mixerMap2Id = m_colorMapsManager.AddColorMapInfo(
      {m_colorMaps, ColorMapName::_NULL, RandomColorMaps::EMPTY});
  m_prevMixerMap2 = m_colorMapsManager.GetColorMapPtr(m_mixerMap2Id);
}

void Colorizer::ChangeColorMode()
{
  if (m_forcedColorMode != IfsDancersFx::ColorMode::_NULL)
  {
    m_colorMode = m_forcedColorMode;
  }
  else
  {
    m_colorMode = GetNextColorMode();
  }
}

auto Colorizer::GetNextColorMode() -> IfsDancersFx::ColorMode
{
  // clang-format off
  static const Weights<IfsDancersFx::ColorMode> s_colorModeWeights{{
    { IfsDancersFx::ColorMode::MAP_COLORS,            15 },
    { IfsDancersFx::ColorMode::MEGA_MAP_COLOR_CHANGE, 20 },
    { IfsDancersFx::ColorMode::MIX_COLORS,            10 },
    { IfsDancersFx::ColorMode::MEGA_MIX_COLOR_CHANGE, 15 },
    { IfsDancersFx::ColorMode::REVERSE_MIX_COLORS,    10 },
    { IfsDancersFx::ColorMode::SINGLE_COLORS,         20 },
    { IfsDancersFx::ColorMode::SINE_MIX_COLORS,       15 },
    { IfsDancersFx::ColorMode::SINE_MAP_COLORS,       15 },
    }};
  // clang-format on

  return s_colorModeWeights.GetRandomWeighted();
}

void Colorizer::ChangeColorMaps()
{
  m_prevMixerMap1 = m_colorMapsManager.GetColorMapPtr(m_mixerMap1Id);
  m_prevMixerMap2 = m_colorMapsManager.GetColorMapPtr(m_mixerMap2Id);
  m_colorMapsManager.ChangeAllColorMapsNow();

  //  logInfo("prevMixerMap = {}", enumToString(prevMixerMap->GetMapName()));
  //  logInfo("mixerMap = {}", enumToString(mixerMap->GetMapName()));
  m_colorMapChangeCompleted =
      GetRandInRange(MIN_COLOR_MAP_CHANGE_COMPLETED, MAX_COLOR_MAP_CHANGE_COMPLETED);
  m_tAwayFromBaseColor = GetRandInRange(MIN_T_AWAY_FROM_BASE_COLOR, MAX_T_AWAY_FROM_BASE_COLOR);
  m_countSinceColorMapChange = m_colorMapChangeCompleted;
}

auto Colorizer::GetNextMixerMapColor(const float t, const float x, const float y) const -> Pixel
{
  //  const float angle = y == 0.0F ? m_half_pi : std::atan2(y, x);
  //  const Pixel nextColor = mixerMap1->GetColor((m_pi + angle) / m_two_pi);
  const Pixel nextColor =
      IColorMap::GetColorMix(m_colorMapsManager.GetColorMap(m_mixerMap1Id).GetColor(x),
                             m_colorMapsManager.GetColorMap(m_mixerMap2Id).GetColor(y), t);
  //  const Pixel nextColor = m_colorMapsManager.GetColorMap(m_mixerMap1Id).GetColor(x);
  if (m_countSinceColorMapChange == 0)
  {
    return nextColor;
  }

  const float tTransition = static_cast<float>(m_countSinceColorMapChange) /
                            static_cast<float>(m_colorMapChangeCompleted);
  m_countSinceColorMapChange--;
  const Pixel prevNextColor =
      IColorMap::GetColorMix(m_prevMixerMap1->GetColor(x), m_prevMixerMap2->GetColor(y), t);
  return IColorMap::GetColorMix(nextColor, prevNextColor, tTransition);
}

auto Colorizer::GetMixedColor(const Pixel& baseColor,
                              const uint32_t hitCount,
                              const float brightness,
                              const bool lowGamma,
                              const float tMix,
                              const float x,
                              const float y) -> Pixel
{
  const float logAlpha =
      m_maxHitCount <= 1 ? 1.0F : std::log(static_cast<float>(hitCount)) / m_logMaxHitCount;

  Pixel mixColor;
  float tBaseMix = 1.0F - m_tAwayFromBaseColor;

  switch (m_colorMode)
  {
    case IfsDancersFx::ColorMode::MAP_COLORS:
    case IfsDancersFx::ColorMode::MEGA_MAP_COLOR_CHANGE:
    {
      mixColor = GetNextMixerMapColor(brightness * logAlpha, x, y);
      if (m_colorMode == IfsDancersFx::ColorMode::MAP_COLORS)
      {
        tBaseMix = 1.0F - m_tAwayFromBaseColor;
      }
      else
      {
        constexpr float MIN_T_BASE_MIX = 0.3;
        constexpr float MAX_T_BASE_MIX = 0.5;
        tBaseMix = GetRandInRange(MIN_T_BASE_MIX, MAX_T_BASE_MIX);
      }
      break;
    }

    case IfsDancersFx::ColorMode::MIX_COLORS:
    case IfsDancersFx::ColorMode::REVERSE_MIX_COLORS:
    case IfsDancersFx::ColorMode::MEGA_MIX_COLOR_CHANGE:
    {
      mixColor = GetNextMixerMapColor(tMix, x, y);
      break;
    }

    case IfsDancersFx::ColorMode::SINGLE_COLORS:
    {
      mixColor = baseColor;
      break;
    }

    case IfsDancersFx::ColorMode::SINE_MIX_COLORS:
    case IfsDancersFx::ColorMode::SINE_MAP_COLORS:
    {
      constexpr float INITIAL_FREQ = 20.0;
      constexpr float T_MIX_FACTOR = 0.5;
      constexpr float Z_STEP = 0.1;
      static float s_freq = INITIAL_FREQ;
      static float s_z = 0.0;

      mixColor = GetNextMixerMapColor(T_MIX_FACTOR * (1.0F + std::sin(s_freq * s_z)), x, y);
      s_z += Z_STEP;
      if (m_colorMode == IfsDancersFx::ColorMode::SINE_MAP_COLORS)
      {
        tBaseMix = 1.0F - m_tAwayFromBaseColor;
      }
      break;
    }

    default:
      throw std::logic_error("Unknown ColorMode");
  }

  if (m_colorMode == IfsDancersFx::ColorMode::REVERSE_MIX_COLORS)
  {
    mixColor = IColorMap::GetColorMix(mixColor, baseColor, tBaseMix);
  }
  else
  {
    mixColor = IColorMap::GetColorMix(baseColor, mixColor, tBaseMix);
  }

  return lowGamma ? m_lowGammaCorrect.GetCorrection(brightness * logAlpha, mixColor)
                  : m_mainGammaCorrect.GetCorrection(brightness * logAlpha, mixColor);
}

#if __cplusplus <= 201402L
} // namespace IFS
} // namespace GOOM
#else
} // namespace GOOM::IFS
#endif
