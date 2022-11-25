#pragma once

#include <cstdint>

namespace GOOM::UTILS
{

class AdaptiveExposure
{
public:
  static constexpr float MIN_EXPOSURE     = 0.01F;
  static constexpr float MAX_EXPOSURE     = 100.0F;
  static constexpr float INITIAL_EXPOSURE = MIN_EXPOSURE;

  AdaptiveExposure() noexcept = default;

  void Start();

  void UpdateAverageLuminance(float averageLuminance);
  [[nodiscard]] auto GetCurrentExposure() const -> float;

private:
  static constexpr uint32_t RAMP_UP_PERIOD = 10;
  uint64_t m_updateNum                     = 0;
  float m_currentExposure                  = INITIAL_EXPOSURE;
};

inline auto AdaptiveExposure::GetCurrentExposure() const -> float
{
  return m_currentExposure;
}

} // namespace GOOM::UTILS
