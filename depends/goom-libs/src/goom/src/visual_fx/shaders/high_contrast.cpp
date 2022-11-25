#include "high_contrast.h"


namespace GOOM::VISUAL_FX::SHADERS
{

using UTILS::MATH::IGoomRand;

HighContrast::HighContrast(const PluginInfo& goomInfo, const IGoomRand& goomRand) noexcept
  : m_goomInfo{goomInfo}, m_goomRand{goomRand}
{
}

void HighContrast::Start()
{
  m_highContrastT.Reset();
  m_highContrastOnTimer.ResetToZero();
  m_highContrastOffTimer.ResetToZero();

  ResetValues();
}

inline void HighContrast::ResetValues()
{
  m_currentContrast                = DEFAULT_CONTRAST;
  m_currentBrightness              = DEFAULT_BRIGHTNESS;
  m_currentContrastMinChannelValue = 0.0F;
  m_maxContrastMinChannelValue     = 0.0F;
}

void HighContrast::ChangeHighContrast()
{
  if (!m_highContrastOffTimer.Finished())
  {
    return;
  }
  if (!m_highContrastOnTimer.Finished())
  {
    return;
  }

  if (static constexpr float PROB_CONTRAST = 0.001F;
      (0 == m_goomInfo.GetSoundEvents().GetTimeSinceLastGoom()) &&
      m_goomRand.ProbabilityOf(PROB_CONTRAST))
  {
    m_highContrastT.Reset();
    m_highContrastOnTimer.ResetToZero();
    static constexpr auto MIN_CONTRAST_MIN_CHAN = -0.5F;
    static constexpr auto MAX_CONTRAST_MIN_CHAN = -0.2F;
    m_maxContrastMinChannelValue =
        m_goomRand.GetRandInRange(MIN_CONTRAST_MIN_CHAN, MAX_CONTRAST_MIN_CHAN);
  }
}

void HighContrast::UpdateHighContrast()
{
  m_highContrastT.Increment();
  m_highContrastOnTimer.Increment();
  m_highContrastOffTimer.Increment();

  if (!m_highContrastOffTimer.Finished())
  {
    return;
  }

  if (!m_highContrastOnTimer.Finished())
  {
    static constexpr auto HIGH_CONTRAST = 1.01F;
    m_currentContrast = STD20::lerp(DEFAULT_CONTRAST, HIGH_CONTRAST, m_highContrastT());
    m_currentContrastMinChannelValue =
        STD20::lerp(0.0F, m_maxContrastMinChannelValue, m_highContrastT());
    static constexpr auto CONTRAST_BRIGHTNESS = 1.1F;
    m_currentBrightness = STD20::lerp(DEFAULT_BRIGHTNESS, CONTRAST_BRIGHTNESS, m_highContrastT());

    return;
  }

  if (m_highContrastOnTimer.JustFinished())
  {
    m_highContrastOffTimer.ResetToZero();
    ResetValues();
    return;
  }

  ChangeHighContrast();
}

} // namespace GOOM::VISUAL_FX::SHADERS
