#include "after_effects_states.h"

#include "filter_fx/filter_consts.h"
#include "utils/math/goom_rand_base.h"
#include "utils/timer.h"

#include <memory>

namespace GOOM::FILTER_FX::AFTER_EFFECTS
{

using UTILS::Timer;
using UTILS::MATH::IGoomRand;

static constexpr auto DEFAULT_BLOCKY_WAVY_EFFECT      = false;
static constexpr auto DEFAULT_HYPERCOS_OVERLAY_EFFECT = false;
static constexpr auto DEFAULT_IMAGE_VELOCITY_EFFECT   = false;
static constexpr auto DEFAULT_NOISE_EFFECT            = false;
static constexpr auto DEFAULT_PLANE_EFFECT            = false;
static constexpr auto DEFAULT_ROTATION_EFFECT         = false;
static constexpr auto DEFAULT_TAN_EFFECT              = false;
static constexpr auto DEFAULT_XY_LERP_EFFECT          = false;

class AfterEffectsStates::EffectState
{
public:
  EffectState(const IGoomRand& goomRand,
              bool turnedOn,
              float probabilityOfEffectRepeated,
              uint32_t effectOffTime) noexcept;

  void UpdateTimer();
  void UpdateState(float probabilityOfEffect);
  void SetState(bool value);
  void CheckPendingOffTimerReset();

  [[nodiscard]] auto IsTurnedOn() const -> bool;

private:
  const IGoomRand& m_goomRand;
  const float m_probabilityOfEffectRepeated;
  bool m_turnedOn;
  Timer m_offTimer;
  bool m_pendingOffTimerReset = false;
};

AfterEffectsStates::AfterEffectsStates(const IGoomRand& goomRand,
                                       const AfterEffectsProbabilityMap& repeatProbabilities,
                                       const AfterEffectsOffTimeMap& offTimes) noexcept
  : m_blockyWavyEffect{std::make_unique<EffectState>(
        goomRand,
        DEFAULT_BLOCKY_WAVY_EFFECT,
        repeatProbabilities[AfterEffectsTypes::BLOCK_WAVY],
        offTimes[AfterEffectsTypes::BLOCK_WAVY])},
    m_hypercosOverlayEffect{
        std::make_unique<EffectState>(goomRand,
                                      DEFAULT_HYPERCOS_OVERLAY_EFFECT,
                                      repeatProbabilities[AfterEffectsTypes::HYPERCOS],
                                      offTimes[AfterEffectsTypes::HYPERCOS])},
    m_imageVelocityEffect{
        std::make_unique<EffectState>(goomRand,
                                      DEFAULT_IMAGE_VELOCITY_EFFECT,
                                      repeatProbabilities[AfterEffectsTypes::IMAGE_VELOCITY],
                                      offTimes[AfterEffectsTypes::IMAGE_VELOCITY])},
    m_noiseEffect{std::make_unique<EffectState>(goomRand,
                                                DEFAULT_NOISE_EFFECT,
                                                repeatProbabilities[AfterEffectsTypes::NOISE],
                                                offTimes[AfterEffectsTypes::NOISE])},
    m_planeEffect{std::make_unique<EffectState>(goomRand,
                                                DEFAULT_PLANE_EFFECT,
                                                repeatProbabilities[AfterEffectsTypes::PLANES],
                                                offTimes[AfterEffectsTypes::PLANES])},
    m_rotationEffect{std::make_unique<EffectState>(goomRand,
                                                   DEFAULT_ROTATION_EFFECT,
                                                   repeatProbabilities[AfterEffectsTypes::ROTATION],
                                                   offTimes[AfterEffectsTypes::ROTATION])},
    m_tanEffect{std::make_unique<EffectState>(goomRand,
                                              DEFAULT_TAN_EFFECT,
                                              repeatProbabilities[AfterEffectsTypes::TAN_EFFECT],
                                              offTimes[AfterEffectsTypes::TAN_EFFECT])},
    m_xyLerpEffect{
        std::make_unique<EffectState>(goomRand,
                                      DEFAULT_XY_LERP_EFFECT,
                                      repeatProbabilities[AfterEffectsTypes::XY_LERP_EFFECT],
                                      offTimes[AfterEffectsTypes::XY_LERP_EFFECT])}
{
}

AfterEffectsStates::~AfterEffectsStates() noexcept = default;

auto AfterEffectsStates::UpdateFilterSettingsFromStates(
    AfterEffectsSettings& afterEffectsSettings) const -> void
{
  afterEffectsSettings.hypercosOverlay = m_hypercosOverlay;

  afterEffectsSettings.active[AfterEffectsTypes::BLOCK_WAVY] = m_blockyWavyEffect->IsTurnedOn();
  afterEffectsSettings.active[AfterEffectsTypes::HYPERCOS] = m_hypercosOverlayEffect->IsTurnedOn();
  afterEffectsSettings.active[AfterEffectsTypes::IMAGE_VELOCITY] =
      m_imageVelocityEffect->IsTurnedOn();
  afterEffectsSettings.active[AfterEffectsTypes::NOISE]          = m_noiseEffect->IsTurnedOn();
  afterEffectsSettings.active[AfterEffectsTypes::PLANES]         = m_planeEffect->IsTurnedOn();
  afterEffectsSettings.active[AfterEffectsTypes::ROTATION]       = m_rotationEffect->IsTurnedOn();
  afterEffectsSettings.active[AfterEffectsTypes::TAN_EFFECT]     = m_tanEffect->IsTurnedOn();
  afterEffectsSettings.active[AfterEffectsTypes::XY_LERP_EFFECT] = m_xyLerpEffect->IsTurnedOn();
}

auto AfterEffectsStates::TurnPlaneEffectOn() -> void
{
  if constexpr (ALL_AFTER_EFFECTS_TURNED_OFF)
  {
    return;
  }

  m_planeEffect->SetState(true);
}

auto AfterEffectsStates::SetDefaults() -> void
{
  m_hypercosOverlay = HypercosOverlay::NONE;
}

auto AfterEffectsStates::UpdateTimers() -> void
{
  if constexpr (ALL_AFTER_EFFECTS_TURNED_OFF)
  {
    return;
  }

  m_blockyWavyEffect->UpdateTimer();
  m_hypercosOverlayEffect->UpdateTimer();
  m_imageVelocityEffect->UpdateTimer();
  m_noiseEffect->UpdateTimer();
  m_planeEffect->UpdateTimer();
  m_rotationEffect->UpdateTimer();
  m_tanEffect->UpdateTimer();
  m_xyLerpEffect->UpdateTimer();
}

auto AfterEffectsStates::ResetAllStates(const AfterEffectsProbabilities& effectsProbabilities)
    -> void
{
  if constexpr (ALL_AFTER_EFFECTS_TURNED_OFF)
  {
    return;
  }

  m_hypercosOverlay = effectsProbabilities.hypercosWeights.GetRandomWeighted();

  ResetStandardStates(effectsProbabilities);
}

auto AfterEffectsStates::ResetStandardStates(const AfterEffectsProbabilities& effectsProbabilities)
    -> void
{
  if constexpr (ALL_AFTER_EFFECTS_TURNED_OFF)
  {
    return;
  }

  m_blockyWavyEffect->UpdateState(
      effectsProbabilities.probabilities[AfterEffectsTypes::BLOCK_WAVY]);
  m_hypercosOverlayEffect->UpdateState(
      effectsProbabilities.probabilities[AfterEffectsTypes::HYPERCOS]);
  m_imageVelocityEffect->UpdateState(
      effectsProbabilities.probabilities[AfterEffectsTypes::IMAGE_VELOCITY]);
  m_noiseEffect->UpdateState(effectsProbabilities.probabilities[AfterEffectsTypes::NOISE]);
  m_planeEffect->UpdateState(effectsProbabilities.probabilities[AfterEffectsTypes::PLANES]);
  m_rotationEffect->UpdateState(effectsProbabilities.probabilities[AfterEffectsTypes::ROTATION]);
  m_tanEffect->UpdateState(effectsProbabilities.probabilities[AfterEffectsTypes::TAN_EFFECT]);
  m_xyLerpEffect->UpdateState(
      effectsProbabilities.probabilities[AfterEffectsTypes::XY_LERP_EFFECT]);

  // TODO(glk) - sort out this hypercos special case hack.
  if (HypercosOverlay::NONE == m_hypercosOverlay)
  {
    m_hypercosOverlayEffect->SetState(false);
  }
  if (not m_hypercosOverlayEffect->IsTurnedOn())
  {
    m_hypercosOverlay = HypercosOverlay::NONE;
  }
}

auto AfterEffectsStates::CheckForPendingOffTimers() -> void
{
  if constexpr (ALL_AFTER_EFFECTS_TURNED_OFF)
  {
    return;
  }

  m_blockyWavyEffect->CheckPendingOffTimerReset();
  m_hypercosOverlayEffect->CheckPendingOffTimerReset();
  m_imageVelocityEffect->CheckPendingOffTimerReset();
  m_noiseEffect->CheckPendingOffTimerReset();
  m_planeEffect->CheckPendingOffTimerReset();
  m_rotationEffect->CheckPendingOffTimerReset();
  m_tanEffect->CheckPendingOffTimerReset();
  m_xyLerpEffect->CheckPendingOffTimerReset();
}

inline AfterEffectsStates::EffectState::EffectState(const UTILS::MATH::IGoomRand& goomRand,
                                                    const bool turnedOn,
                                                    const float probabilityOfEffectRepeated,
                                                    const uint32_t effectOffTime) noexcept
  : m_goomRand{goomRand},
    m_probabilityOfEffectRepeated{probabilityOfEffectRepeated},
    m_turnedOn{turnedOn},
    m_offTimer{effectOffTime, true}
{
}

inline auto AfterEffectsStates::EffectState::UpdateTimer() -> void
{
  m_offTimer.Increment();
}

inline auto AfterEffectsStates::EffectState::UpdateState(const float probabilityOfEffect) -> void
{
  if (not m_offTimer.Finished())
  {
    return;
  }
  if (m_pendingOffTimerReset)
  {
    return;
  }

  SetState(m_goomRand.ProbabilityOf(probabilityOfEffect));
}

inline auto AfterEffectsStates::EffectState::SetState(const bool value) -> void
{
  const auto previouslyTurnedOn = m_turnedOn;
  m_turnedOn                    = value;

  if (previouslyTurnedOn && m_turnedOn)
  {
    m_turnedOn = m_goomRand.ProbabilityOf(m_probabilityOfEffectRepeated);
  }
  if (previouslyTurnedOn && (not m_turnedOn))
  {
    m_pendingOffTimerReset = true;
  }
}

inline auto AfterEffectsStates::EffectState::CheckPendingOffTimerReset() -> void
{
  if (not m_pendingOffTimerReset)
  {
    return;
  }

  // Wait a while before allowing effect back on.
  m_offTimer.ResetToZero();
  m_pendingOffTimerReset = false;
}

inline auto AfterEffectsStates::EffectState::IsTurnedOn() const -> bool
{
  return m_turnedOn;
}

} // namespace GOOM::FILTER_FX::AFTER_EFFECTS
