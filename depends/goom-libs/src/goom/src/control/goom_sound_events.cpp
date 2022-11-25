#include "goom_sound_events.h"

#include "sound_info.h"

#include <algorithm>

namespace GOOM::CONTROL
{

GoomSoundEvents::GoomSoundEvents(const SoundInfo& soundInfo) noexcept : m_soundInfo{soundInfo}
{
}

auto GoomSoundEvents::Update() noexcept -> void
{
  ++m_updateNum;

  UpdateLastGoom();
  UpdateLastBigGoom();
  CheckSettledGoomLimits();
}

auto GoomSoundEvents::UpdateLastGoom() -> void
{
  // Temps du goom
  // Goom time

  ++m_timeSinceLastGoom;

  if (m_soundInfo.GetAcceleration() > m_goomLimit)
  {
    m_timeSinceLastGoom = 0;
    ++m_totalGoomsInCurrentCycle;
    m_goomPower = m_soundInfo.GetAcceleration() - m_goomLimit;
  }

  if (m_soundInfo.GetAcceleration() > m_maxAccelerationSinceLastReset)
  {
    m_maxAccelerationSinceLastReset = m_soundInfo.GetAcceleration();
  }

  // Toute les 2 secondes: vérifier si le taux de goom est correct et le modifier sinon.
  // Every 2 seconds: check if the goom rate is correct and modify it otherwise.
  if (0 == (m_updateNum % CYCLE_TIME))
  {
    CheckGoomRate();
  }
}

void GoomSoundEvents::CheckGoomRate()
{
  UpdateGoomLimit();
  Ensures((GOOM_LIMIT_MIN <= m_goomLimit) && (m_goomLimit <= GOOM_LIMIT_MAX));

  m_totalGoomsInCurrentCycle      = 0;
  m_maxAccelerationSinceLastReset = 0.0F;
  m_bigGoomLimit                  = BIG_GOOM_FACTOR * m_goomLimit;
}

static constexpr auto NUM_GOOMS_IN_SHORT_CYCLE          = 4U;
static constexpr auto GOOM_LIMIT_SHORT_CYCLE_INCREMENT  = 0.02F;
static constexpr auto NUM_GOOMS_IN_MEDIUM_CYCLE         = 7U;
static constexpr auto GOOM_LIMIT_MEDIUM_CYCLE_INCREMENT = 0.03F;
static constexpr auto NUM_GOOMS_IN_LONG_CYCLE           = 16U;
static constexpr auto GOOM_LIMIT_LONG_CYCLE_INCREMENT   = 0.04F;

// Detection des nouveaux goom
// Detection of new goom
void GoomSoundEvents::UpdateGoomLimit()
{
  static constexpr auto VERY_SLOW_SPEED              = 0.9F * SoundInfo::SPEED_MIDPOINT;
  static constexpr auto GOOM_LIMIT_SLOW_SPEED_FACTOR = 0.91F;
  if (m_soundInfo.GetSpeed() < VERY_SLOW_SPEED)
  {
    m_goomLimit *= GOOM_LIMIT_SLOW_SPEED_FACTOR;
  }

  if (m_totalGoomsInCurrentCycle > NUM_GOOMS_IN_LONG_CYCLE)
  {
    m_goomLimit *= 1.0F + GOOM_LIMIT_LONG_CYCLE_INCREMENT;
    m_goomLimit += GOOM_LIMIT_LONG_CYCLE_INCREMENT;
  }
  else if (m_totalGoomsInCurrentCycle > NUM_GOOMS_IN_MEDIUM_CYCLE)
  {
    m_goomLimit *= 1.0F + GOOM_LIMIT_MEDIUM_CYCLE_INCREMENT;
    m_goomLimit += GOOM_LIMIT_MEDIUM_CYCLE_INCREMENT;
  }
  else if (m_totalGoomsInCurrentCycle > NUM_GOOMS_IN_SHORT_CYCLE)
  {
    m_goomLimit += GOOM_LIMIT_SHORT_CYCLE_INCREMENT;
  }
  else if (0 == m_totalGoomsInCurrentCycle)
  {
    static constexpr auto GOOM_LIMIT_ACCELERATION_DECREMENT = 0.03F;
    m_goomLimit = m_maxAccelerationSinceLastReset - GOOM_LIMIT_ACCELERATION_DECREMENT;
  }

  static constexpr auto GOOM_LIMIT_TOO_BIG           = 1.1F * SoundInfo::SPEED_MIDPOINT;
  static constexpr auto GOOM_LIMIT_TOO_BIG_DECREMENT = 0.02F;
  if ((1 == m_totalGoomsInCurrentCycle) && (m_goomLimit > GOOM_LIMIT_TOO_BIG))
  {
    m_goomLimit -= GOOM_LIMIT_TOO_BIG_DECREMENT;
  }

  m_goomLimit = std::clamp(m_goomLimit, GOOM_LIMIT_MIN, GOOM_LIMIT_MAX);
}

auto GoomSoundEvents::UpdateLastBigGoom() -> void
{
  ++m_timeSinceLastBigGoom;
  if (m_timeSinceLastBigGoom <= MAX_BIG_GOOM_DURATION)
  {
    return;
  }

  if ((m_soundInfo.GetSpeed() > BIG_GOOM_SPEED_LIMIT) &&
      (m_soundInfo.GetAcceleration() > m_bigGoomLimit))
  {
    m_timeSinceLastBigGoom = 0;
  }
}

inline void GoomSoundEvents::CheckSettledGoomLimits()
{
  if (static constexpr auto NUM_UPDATES_TO_SETTLE = 5U; m_updateNum <= NUM_UPDATES_TO_SETTLE)
  {
    m_goomLimit    = m_soundInfo.GetAcceleration() + GOOM_LIMIT_SHORT_CYCLE_INCREMENT;
    m_bigGoomLimit = BIG_GOOM_FACTOR * m_goomLimit;
  }
}

} // namespace GOOM::CONTROL
