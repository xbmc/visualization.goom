#include "adaptive_exposure.h"

#include "utils/math/misc.h"

#include <algorithm>

namespace GOOM::UTILS
{

void AdaptiveExposure::Start()
{
  m_updateNum       = 0;
  m_currentExposure = INITIAL_EXPOSURE;
}

void AdaptiveExposure::UpdateAverageLuminance(float averageLuminance)
{
  ++m_updateNum;

  if (averageLuminance < (1.0F / MAX_EXPOSURE))
  {
    averageLuminance = 1.0F / MAX_EXPOSURE;
  }

  const auto targetExposure = std::clamp(1.0F / averageLuminance, MIN_EXPOSURE, MAX_EXPOSURE);

  static constexpr auto EXPOSURE_LERP_FACTOR = 0.08F;
  m_currentExposure = STD20::lerp(m_currentExposure, targetExposure, EXPOSURE_LERP_FACTOR);

  if (m_updateNum < RAMP_UP_PERIOD)
  {
    // Don't do anything too sudden until things have smoothed down.
    static constexpr auto MIN_GRADUAL_EXPOSURE = 0.90F;
    static constexpr auto MAX_GRADUAL_EXPOSURE = 1.05F;
    m_currentExposure = std::clamp(m_currentExposure, MIN_GRADUAL_EXPOSURE, MAX_GRADUAL_EXPOSURE);
  }
}

} // namespace GOOM::UTILS
