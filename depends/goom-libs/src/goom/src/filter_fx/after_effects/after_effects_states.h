#pragma once

#include "after_effects_types.h"
#include "rotation.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"

#include <cstdint>
#include <memory>

namespace GOOM::UTILS::MATH
{
class IGoomRand;
}

namespace GOOM::FILTER_FX::AFTER_EFFECTS
{

enum class HypercosOverlay
{
  NONE,
  MODE0,
  MODE1,
  MODE2,
  MODE3,
  _num // unused, and marks the enum end
};

class AfterEffectsStates
{
public:
  using AfterEffectsActiveMap      = UTILS::EnumMap<AfterEffectsTypes, bool>;
  using AfterEffectsOffTimeMap     = UTILS::EnumMap<AfterEffectsTypes, uint32_t>;
  using AfterEffectsProbabilityMap = UTILS::EnumMap<AfterEffectsTypes, float>;

  struct AfterEffectsSettings
  {
    HypercosOverlay hypercosOverlay;
    AfterEffectsActiveMap active;

    RotationAdjustments rotationAdjustments;
  };
  struct AfterEffectsProbabilities
  {
    UTILS::MATH::Weights<HypercosOverlay> hypercosWeights;
    AfterEffectsProbabilityMap probabilities;
  };

  AfterEffectsStates(const UTILS::MATH::IGoomRand& goomRand,
                     const AfterEffectsProbabilityMap& repeatProbabilities,
                     const AfterEffectsOffTimeMap& offTimes) noexcept;
  AfterEffectsStates(const AfterEffectsStates&) noexcept = delete;
  AfterEffectsStates(AfterEffectsStates&&) noexcept      = delete;
  ~AfterEffectsStates() noexcept;
  auto operator=(const AfterEffectsStates&) -> AfterEffectsStates& = delete;
  auto operator=(AfterEffectsStates&&) -> AfterEffectsStates&      = delete;

  auto TurnPlaneEffectOn() -> void;

  auto SetDefaults() -> void;
  auto UpdateTimers() -> void;
  auto ResetAllStates(const AfterEffectsProbabilities& effectsProbabilities) -> void;
  auto ResetStandardStates(const AfterEffectsProbabilities& effectsProbabilities) -> void;
  auto CheckForPendingOffTimers() -> void;
  auto UpdateFilterSettingsFromStates(AfterEffectsSettings& afterEffectsSettings) const -> void;

private:
  class EffectState;

  HypercosOverlay m_hypercosOverlay = HypercosOverlay::NONE;
  std::unique_ptr<EffectState> m_blockyWavyEffect;
  std::unique_ptr<EffectState> m_hypercosOverlayEffect;
  std::unique_ptr<EffectState> m_imageVelocityEffect;
  std::unique_ptr<EffectState> m_noiseEffect;
  std::unique_ptr<EffectState> m_planeEffect;
  std::unique_ptr<EffectState> m_rotationEffect;
  std::unique_ptr<EffectState> m_tanEffect;
  std::unique_ptr<EffectState> m_xyLerpEffect;
};

} // namespace GOOM::FILTER_FX::AFTER_EFFECTS
