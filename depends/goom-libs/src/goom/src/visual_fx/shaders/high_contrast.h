#pragma once

#include "goom_plugin_info.h"
#include "utils/math/goom_rand.h"
#include "utils/t_values.h"
#include "utils/timer.h"

namespace GOOM::VISUAL_FX::SHADERS
{

class HighContrast
{
public:
  static constexpr float DEFAULT_CONTRAST   = 1.0F;
  static constexpr float DEFAULT_BRIGHTNESS = 1.0F;

  explicit HighContrast(const PluginInfo& goomInfo,
                        const UTILS::MATH::IGoomRand& goomRand) noexcept;

  void Start();

  void ChangeHighContrast();
  void UpdateHighContrast();
  [[nodiscard]] auto GetCurrentContrast() const -> float;
  [[nodiscard]] auto GetCurrentBrightness() const -> float;
  [[nodiscard]] auto GetCurrentContrastMinChannelValue() const -> float;

private:
  const PluginInfo& m_goomInfo;
  const UTILS::MATH::IGoomRand& m_goomRand;

  float m_currentContrast                = DEFAULT_CONTRAST;
  float m_currentBrightness              = DEFAULT_BRIGHTNESS;
  float m_currentContrastMinChannelValue = 0.0F;
  float m_maxContrastMinChannelValue     = 0.0F;
  void ResetValues();

  static constexpr uint32_t NUM_HIGH_CONTRAST_ON_STEPS  = 250;
  static constexpr uint32_t HIGH_CONTRAST_ON_DELAY_TIME = 100;
  static constexpr uint32_t HIGH_CONTRAST_ON_TIME =
      (2 * NUM_HIGH_CONTRAST_ON_STEPS) + HIGH_CONTRAST_ON_DELAY_TIME;
  UTILS::TValue m_highContrastT{UTILS::TValue::StepType::CONTINUOUS_REVERSIBLE,
                                NUM_HIGH_CONTRAST_ON_STEPS,
                                {{1.0F, HIGH_CONTRAST_ON_DELAY_TIME}}};
  UTILS::Timer m_highContrastOnTimer{HIGH_CONTRAST_ON_TIME, true};
  static constexpr uint32_t HIGH_CONTRAST_OFF_TIME = 300;
  UTILS::Timer m_highContrastOffTimer{HIGH_CONTRAST_OFF_TIME, false};
};

inline auto HighContrast::GetCurrentContrast() const -> float
{
  return m_currentContrast;
}

inline auto HighContrast::GetCurrentBrightness() const -> float
{
  return m_currentBrightness;
}

inline auto HighContrast::GetCurrentContrastMinChannelValue() const -> float
{
  return m_currentContrastMinChannelValue;
}

} // namespace GOOM::VISUAL_FX::SHADERS
