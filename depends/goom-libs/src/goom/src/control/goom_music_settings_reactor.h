#pragma once

#include "filter_fx/filter_settings_service.h"
#include "goom_all_visual_fx.h"
#include "goom_events.h"
#include "goom_lock.h"
#include "goom_plugin_info.h"
#include "utils/math/goom_rand_base.h"
#include "utils/name_value_pairs.h"

#include <cstdint>

namespace GOOM
{
class PluginInfo;

namespace CONTROL
{
class GoomAllVisualFx;

class GoomMusicSettingsReactor
{
public:
  GoomMusicSettingsReactor(const PluginInfo& goomInfo,
                           const UTILS::MATH::IGoomRand& goomRand,
                           GoomAllVisualFx& visualFx,
                           const GoomEvents& goomEvents,
                           FILTER_FX::FilterSettingsService& filterSettingsService) noexcept;

  auto Start() -> void;
  auto NewCycle() -> void;

  auto ChangeZoomEffects() -> void;
  auto ChangeFilterModeIfMusicChanges() -> void;

  // gros frein si la musique est calme
  auto BigBreakIfMusicIsCalm() -> void;

  // tout ceci ne sera fait qu'en cas de non-blocage
  auto BigUpdateIfNotLocked() -> void;

  // baisser regulierement la vitesse
  auto RegularlyLowerTheSpeed() -> void;

  [[nodiscard]] auto GetNameValueParams() const -> UTILS::NameValuePairs;

private:
  const PluginInfo& m_goomInfo;
  const UTILS::MATH::IGoomRand& m_goomRand;
  GoomAllVisualFx& m_visualFx;
  using GoomEvent = GoomEvents::GoomEvent;
  const GoomEvents& m_goomEvents;
  FILTER_FX::FilterSettingsService& m_filterSettingsService;

  static constexpr uint32_t NORMAL_UPDATE_LOCK_TIME                = 50;
  static constexpr uint32_t REVERSE_SPEED_AND_STOP_SPEED_LOCK_TIME = 75;
  static constexpr uint32_t REVERSE_SPEED_LOCK_TIME                = 100;
  static constexpr uint32_t MEGA_LENT_LOCK_TIME_INCREASE           = 50;
  static constexpr uint32_t CHANGE_VITESSE_LOCK_TIME_INCREASE      = 50;
  static constexpr uint32_t CHANGE_SWITCH_VALUES_LOCK_TIME         = 150;
  GoomLock m_lock{}; // pour empecher de nouveaux changements

  uint32_t m_updateNum = 0;

  static constexpr int32_t MAX_TIME_BETWEEN_ZOOM_EFFECTS_CHANGE = 200;
  int32_t m_updatesSinceLastZoomEffectsChange = 0; // nombre de Cycle Depuis Dernier Changement
  uint32_t m_previousZoomSpeed                = FILTER_FX::Vitesse::STOP_SPEED;

  static constexpr uint32_t MAX_NUM_STATE_SELECTIONS_BLOCKED = 3;
  uint32_t m_stateSelectionBlocker                           = MAX_NUM_STATE_SELECTIONS_BLOCKED;
  uint32_t m_timeInState                                     = 0;
  auto ChangeState() -> void;
  auto DoChangeState() -> void;

  // Changement d'effet de zoom !
  auto BigNormalUpdate() -> void;
  auto MegaLentUpdate() -> void;
  auto BigUpdate() -> void;
  auto BigBreak() -> void;
  auto ChangeFilterMode() -> void;
  auto ChangeFilterExtraSettings() -> void;
  auto ChangeRotation() -> void;
  auto ChangeTranBufferSwitchValues() -> void;
  auto ChangeSpeedReverse() -> void;
  auto ChangeVitesse() -> void;
  auto ChangeStopSpeeds() -> void;
};

inline auto GoomMusicSettingsReactor::Start() -> void
{
  m_updateNum   = 0;
  m_timeInState = 0;

  DoChangeState();
}

inline auto GoomMusicSettingsReactor::NewCycle() -> void
{
  ++m_updateNum;
  ++m_timeInState;
  m_lock.Update();
}

inline auto GoomMusicSettingsReactor::BigBreakIfMusicIsCalm() -> void
{
  static constexpr auto CALM_SOUND_SPEED = 0.3F;
  static constexpr auto CALM_CYCLES      = 16U;

  if ((m_goomInfo.GetSoundEvents().GetSoundInfo().GetSpeed() < CALM_SOUND_SPEED) and
      (m_filterSettingsService.GetROVitesse().IsFasterThan(FILTER_FX::Vitesse::CALM_SPEED)) and
      (0 == (m_updateNum % CALM_CYCLES)))
  {
    BigBreak();
  }
}

inline auto GoomMusicSettingsReactor::BigBreak() -> void
{
  static constexpr auto SLOWER_BY = 3U;
  m_filterSettingsService.GetRWVitesse().GoSlowerBy(SLOWER_BY);

  m_visualFx.ChangeAllFxColorMaps();
  m_visualFx.ChangeDrawPixelBlend();
}

inline auto GoomMusicSettingsReactor::ChangeFilterModeIfMusicChanges() -> void
{
  if (((0 == m_goomInfo.GetSoundEvents().GetTimeSinceLastGoom()) ||
       (m_updatesSinceLastZoomEffectsChange > MAX_TIME_BETWEEN_ZOOM_EFFECTS_CHANGE)) &&
      m_goomEvents.Happens(GoomEvent::CHANGE_FILTER_MODE))
  {
    ChangeFilterMode();
  }
}

inline auto GoomMusicSettingsReactor::ChangeFilterMode() -> void
{
  m_filterSettingsService.SetNewRandomFilter();
  m_visualFx.UpdateFilterSettings(std::as_const(m_filterSettingsService).GetFilterSettings());
  m_visualFx.RefreshAllFx();
  m_filterSettingsService.NotifyUpdatedFilterEffectsSettings();
}

inline auto GoomMusicSettingsReactor::ChangeFilterExtraSettings() -> void
{
  m_filterSettingsService.ChangeMilieu();
  m_filterSettingsService.ResetRandomExtraEffects();
}

inline auto GoomMusicSettingsReactor::ChangeRotation() -> void
{
  if (m_goomEvents.Happens(GoomEvent::FILTER_STOP_ROTATION))
  {
    m_filterSettingsService.TurnOffRotation();
  }
  else if (m_goomEvents.Happens(GoomEvent::FILTER_DECREASE_ROTATION))
  {
    static constexpr auto ROTATE_SLOWER_FACTOR = 0.9F;
    m_filterSettingsService.MultiplyRotation(ROTATE_SLOWER_FACTOR);
  }
  else if (m_goomEvents.Happens(GoomEvent::FILTER_INCREASE_ROTATION))
  {
    static constexpr auto ROTATE_FASTER_FACTOR = 1.1F;
    m_filterSettingsService.MultiplyRotation(ROTATE_FASTER_FACTOR);
  }
  else if (m_goomEvents.Happens(GoomEvent::FILTER_TOGGLE_ROTATION))
  {
    m_filterSettingsService.ToggleRotationDirection();
  }
}

inline auto GoomMusicSettingsReactor::RegularlyLowerTheSpeed() -> void
{
  static constexpr auto LOWER_SPEED_CYCLES = 73U;

  if ((0 == (m_updateNum % LOWER_SPEED_CYCLES)) &&
      (m_filterSettingsService.GetROVitesse().IsFasterThan(FILTER_FX::Vitesse::FAST_SPEED)))
  {
    m_filterSettingsService.GetRWVitesse().GoSlowerBy(1U);
  }
}

inline auto GoomMusicSettingsReactor::BigUpdateIfNotLocked() -> void
{
  if (m_lock.IsLocked())
  {
    return;
  }

  BigUpdate();
}

inline auto GoomMusicSettingsReactor::BigUpdate() -> void
{
  // Reperage de goom (acceleration forte de l'acceleration du volume).
  // Coup de boost de la vitesse si besoin.
  // Goom tracking (strong acceleration of volume acceleration).
  // Speed boost if needed.
  if (0 == m_goomInfo.GetSoundEvents().GetTimeSinceLastGoom())
  {
    BigNormalUpdate();
  }

  // mode mega-lent
  if (m_goomEvents.Happens(GoomEvent::CHANGE_TO_MEGA_LENT_MODE))
  {
    MegaLentUpdate();
  }
}

inline auto GoomMusicSettingsReactor::BigNormalUpdate() -> void
{
  m_lock.SetLockTime(NORMAL_UPDATE_LOCK_TIME);

  ChangeState();
  ChangeSpeedReverse();
  ChangeStopSpeeds();
  ChangeRotation();
  ChangeFilterExtraSettings();
  ChangeVitesse();
  ChangeTranBufferSwitchValues();
  m_visualFx.ChangeAllFxColorMaps();

  static constexpr auto PROB_SINGLE_BUFFER_DOTS = 1.0F / 20.0F;
  m_visualFx.SetSingleBufferDots(m_goomRand.ProbabilityOf(PROB_SINGLE_BUFFER_DOTS));
}

inline auto GoomMusicSettingsReactor::MegaLentUpdate() -> void
{
  m_lock.IncreaseLockTime(MEGA_LENT_LOCK_TIME_INCREASE);

  m_visualFx.ChangeAllFxColorMaps();
  m_filterSettingsService.GetRWVitesse().SetVitesse(FILTER_FX::Vitesse::SLOWEST_SPEED);
  m_filterSettingsService.SetDefaultTranLerpIncrement();
  m_filterSettingsService.SetTranLerpToMaxSwitchMult(1.0F);
}

inline auto GoomMusicSettingsReactor::ChangeSpeedReverse() -> void
{
  // Retablir le zoom avant.
  // Restore zoom in.

  static constexpr auto REVERSE_VITESSE_CYCLES = 13U;

  if ((m_filterSettingsService.GetROVitesse().GetReverseVitesse()) &&
      ((m_updateNum % REVERSE_VITESSE_CYCLES) != 0) &&
      m_goomEvents.Happens(GoomEvent::FILTER_REVERSE_OFF_AND_STOP_SPEED))
  {
    m_filterSettingsService.GetRWVitesse().SetReverseVitesse(false);
    m_filterSettingsService.GetRWVitesse().SetVitesse(FILTER_FX::Vitesse::SLOW_SPEED);
    m_lock.SetLockTime(REVERSE_SPEED_AND_STOP_SPEED_LOCK_TIME);
  }
  if (m_goomEvents.Happens(GoomEvent::FILTER_REVERSE_ON))
  {
    m_filterSettingsService.GetRWVitesse().SetReverseVitesse(true);
    m_lock.SetLockTime(REVERSE_SPEED_LOCK_TIME);
  }
}

inline auto GoomMusicSettingsReactor::ChangeStopSpeeds() -> void
{
  if (m_goomEvents.Happens(GoomEvent::FILTER_VITESSE_STOP_SPEED_MINUS1))
  {
    m_filterSettingsService.GetRWVitesse().SetVitesse(FILTER_FX::Vitesse::SLOWEST_SPEED);
  }
  else if (m_goomEvents.Happens(GoomEvent::FILTER_VITESSE_STOP_SPEED))
  {
    m_filterSettingsService.GetRWVitesse().SetVitesse(FILTER_FX::Vitesse::STOP_SPEED);
  }
}

inline auto GoomMusicSettingsReactor::ChangeTranBufferSwitchValues() -> void
{
  if (m_lock.GetLockTime() > CHANGE_SWITCH_VALUES_LOCK_TIME)
  {
    m_filterSettingsService.SetDefaultTranLerpIncrement();
    m_filterSettingsService.SetTranLerpToMaxSwitchMult(1.0F);
  }
}

inline auto GoomMusicSettingsReactor::ChangeState() -> void
{
  if (m_stateSelectionBlocker > 0)
  {
    --m_stateSelectionBlocker;
    return;
  }
  if (!m_goomEvents.Happens(GoomEvent::CHANGE_STATE))
  {
    return;
  }

  DoChangeState();

  m_stateSelectionBlocker = MAX_NUM_STATE_SELECTIONS_BLOCKED;
}

inline auto GoomMusicSettingsReactor::DoChangeState() -> void
{
  m_visualFx.SetNextState();
  m_visualFx.ChangeAllFxColorMaps();

  m_timeInState = 0;
}

} // namespace CONTROL
} // namespace GOOM
