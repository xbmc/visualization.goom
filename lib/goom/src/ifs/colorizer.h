#ifndef VISUALIZATION_GOOM_COLORIZER_H
#define VISUALIZATION_GOOM_COLORIZER_H

#include "goom_graphic.h"
#include "goomutils/colormaps.h"
#include "goomutils/colorutils.h"
#include "goomutils/random_colormaps.h"
#include "goomutils/random_colormaps_manager.h"
#include "ifs_dancers_fx.h"

#include <cmath>
#include <cstdint>
#include <memory>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace IFS
{
#else
namespace GOOM::IFS
{
#endif

class Colorizer
{
public:
  Colorizer() noexcept;
  ~Colorizer() noexcept = default;
  Colorizer(const Colorizer&) = delete;
  Colorizer(const Colorizer&&) = delete;
  auto operator=(const Colorizer&) -> Colorizer& = delete;
  auto operator=(const Colorizer&&) -> Colorizer& = delete;

  void SetWeightedColorMaps(std::shared_ptr<UTILS::RandomColorMaps> weightedMaps);

  auto GetColorMaps() const -> const UTILS::RandomColorMaps&;

  auto GetColorMode() const -> IfsDancersFx::ColorMode;
  void SetForcedColorMode(IfsDancersFx::ColorMode val);
  void ChangeColorMode();

  void ChangeColorMaps();

  void SetMaxHitCount(uint32_t val);

  [[nodiscard]] auto GetMixedColor(const Pixel& baseColor,
                                   uint32_t hitCount,
                                   float brightness,
                                   bool lowGamma,
                                   float tMix,
                                   float x,
                                   float y) -> Pixel;

private:
  std::shared_ptr<UTILS::RandomColorMaps> m_colorMaps{};
  UTILS::RandomColorMapsManager m_colorMapsManager{};
  uint32_t m_mixerMap1Id{};
  std::shared_ptr<const UTILS::IColorMap> m_prevMixerMap1{};
  uint32_t m_mixerMap2Id{};
  std::shared_ptr<const UTILS::IColorMap> m_prevMixerMap2{};
  mutable uint32_t m_countSinceColorMapChange = 0;
  static constexpr uint32_t MIN_COLOR_MAP_CHANGE_COMPLETED = 500;
  static constexpr uint32_t MAX_COLOR_MAP_CHANGE_COMPLETED = 1000;
  uint32_t m_colorMapChangeCompleted = MIN_COLOR_MAP_CHANGE_COMPLETED;

  IfsDancersFx::ColorMode m_colorMode = IfsDancersFx::ColorMode::MAP_COLORS;
  IfsDancersFx::ColorMode m_forcedColorMode = IfsDancersFx::ColorMode::_NULL;
  uint32_t m_maxHitCount = 0;
  float m_logMaxHitCount = 0.0;
  static constexpr float MIN_T_AWAY_FROM_BASE_COLOR = 0.0F;
  static constexpr float MAX_T_AWAY_FROM_BASE_COLOR = 0.4F;
  static constexpr float INITIAL_T_AWAY_FROM_BASE_COLOR = 0.0F;
  float m_tAwayFromBaseColor = INITIAL_T_AWAY_FROM_BASE_COLOR; // in [0, 1]
  static auto GetNextColorMode() -> IfsDancersFx::ColorMode;
  [[nodiscard]] auto GetNextMixerMapColor(float t, float x, float y) const -> Pixel;

  static constexpr float MAIN_GAMMA = 10.0F;
  static constexpr float MAIN_GAMMA_THRESHOLD = 0.01F;
  const UTILS::GammaCorrection m_mainGammaCorrect{MAIN_GAMMA, MAIN_GAMMA_THRESHOLD};

  static constexpr float LOW_GAMMA = 4.0F;
  static constexpr float LOW_GAMMA_THRESHOLD = 0.01F;
  const UTILS::GammaCorrection m_lowGammaCorrect{LOW_GAMMA, LOW_GAMMA_THRESHOLD};
};

inline auto Colorizer::GetColorMaps() const -> const UTILS::RandomColorMaps&
{
  return *m_colorMaps;
}

inline auto Colorizer::GetColorMode() const -> IfsDancersFx::ColorMode
{
  return m_colorMode;
}

inline void Colorizer::SetForcedColorMode(const IfsDancersFx::ColorMode val)
{
  m_forcedColorMode = val;
}

inline void Colorizer::SetMaxHitCount(const uint32_t val)
{
  m_maxHitCount = val;
  m_logMaxHitCount = std::log(static_cast<float>(m_maxHitCount));
}

#if __cplusplus <= 201402L
} // namespace IFS
} // namespace GOOM
#else
} // namespace GOOM::IFS
#endif

#endif //VISUALIZATION_GOOM_COLORIZER_H
