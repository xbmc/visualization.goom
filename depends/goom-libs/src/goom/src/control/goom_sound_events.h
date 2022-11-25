#pragma once

#include "sound_info.h"

#include <cstdint>

namespace GOOM::CONTROL
{

class GoomSoundEvents
{
public:
  explicit GoomSoundEvents(const SoundInfo& soundInfo) noexcept;

  [[nodiscard]] auto GetSoundInfo() const noexcept -> const SoundInfo&;

  auto Update() noexcept -> void;

  [[nodiscard]] auto GetTimeSinceLastGoom() const noexcept -> uint32_t;
  [[nodiscard]] auto GetTimeSinceLastBigGoom() const noexcept -> uint32_t;

  // Number of Gooms since last reset (every 'CYCLE_TIME')
  static constexpr uint32_t CYCLE_TIME = 64;
  [[nodiscard]] auto GetTotalGoomsInCurrentCycle() const noexcept -> uint32_t;

  // Power of the last Goom [0..1]
  [[nodiscard]] auto GetGoomPower() const noexcept -> float;

  // For debugging
  [[nodiscard]] auto GetGoomLimit() const noexcept -> float;
  [[nodiscard]] auto GetBigGoomLimit() const noexcept -> float;

private:
  const SoundInfo& m_soundInfo;

  uint32_t m_updateNum = 0;

  uint32_t m_totalGoomsInCurrentCycle             = 0;
  uint32_t m_timeSinceLastGoom                    = 0;
  static constexpr uint32_t MAX_BIG_GOOM_DURATION = 100;
  uint32_t m_timeSinceLastBigGoom                 = 0;
  float m_goomPower                               = 0.0F;

  static constexpr float GOOM_LIMIT_MIN = 0.0F;
  static constexpr float GOOM_LIMIT_MAX = 1.0F;
  float m_goomLimit                     = 1.0F; // auto-updated limit of goom detection

  static constexpr float BIG_GOOM_SPEED_LIMIT = 1.1F * SoundInfo::SPEED_MIDPOINT;
  static constexpr float BIG_GOOM_FACTOR      = 1.01F;
  float m_bigGoomLimit                        = 1.0F;

  float m_maxAccelerationSinceLastReset = 0.0F;

  auto UpdateLastGoom() -> void;
  auto UpdateLastBigGoom() -> void;
  void CheckGoomRate();
  void UpdateGoomLimit();
  void CheckSettledGoomLimits();
};

inline auto GoomSoundEvents::GetSoundInfo() const noexcept -> const SoundInfo&
{
  return m_soundInfo;
}

inline auto GoomSoundEvents::GetTotalGoomsInCurrentCycle() const noexcept -> uint32_t
{
  return m_totalGoomsInCurrentCycle;
}

inline auto GoomSoundEvents::GetTimeSinceLastGoom() const noexcept -> uint32_t
{
  return m_timeSinceLastGoom;
}

inline auto GoomSoundEvents::GetTimeSinceLastBigGoom() const noexcept -> uint32_t
{
  return m_timeSinceLastBigGoom;
}

inline auto GoomSoundEvents::GetGoomPower() const noexcept -> float
{
  return m_goomPower;
}

inline auto GoomSoundEvents::GetGoomLimit() const noexcept -> float
{
  return m_goomLimit;
}

inline auto GoomSoundEvents::GetBigGoomLimit() const noexcept -> float
{
  return m_bigGoomLimit;
}

} // namespace GOOM::CONTROL
