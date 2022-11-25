#pragma once

#include "after_effects/after_effects_states.h"
#include "after_effects/rotation.h"
#include "filter_settings.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"
#include "utils/propagate_const.h"
#include "zoom_in_coefficients_effect.h"

#include <functional>
#include <memory>
#include <string_view>

namespace GOOM
{
class Pixel;
class PluginInfo;
}

namespace GOOM::FILTER_FX
{

enum class ZoomFilterMode
{
  AMULET_MODE = 0,
  CRYSTAL_BALL_MODE0,
  CRYSTAL_BALL_MODE1,
  DISTANCE_FIELD_MODE0,
  DISTANCE_FIELD_MODE1,
  DISTANCE_FIELD_MODE2,
  EXP_RECIPROCAL_MODE,
  HYPERCOS_MODE0,
  HYPERCOS_MODE1,
  HYPERCOS_MODE2,
  HYPERCOS_MODE3,
  IMAGE_DISPLACEMENT_MODE,
  NORMAL_MODE,
  SCRUNCH_MODE,
  SPEEDWAY_MODE0,
  SPEEDWAY_MODE1,
  SPEEDWAY_MODE2,
  WATER_MODE,
  WAVE_MODE0,
  WAVE_MODE1,
  Y_ONLY_MODE,
  _num // unused, and marks the enum end
};

class FilterSettingsService
{
public:
  using CreateZoomInCoefficientsEffectFunc =
      std::function<std::shared_ptr<IZoomInCoefficientsEffect>(
          ZoomFilterMode filterMode,
          const UTILS::MATH::IGoomRand& goomRand,
          const std::string& resourcesDirectory)>;
  // TODO(glk) - Visual Studio doesn't like a trailing return type in above function definition.

  FilterSettingsService(const GOOM::PluginInfo& goomInfo,
                        const UTILS::MATH::IGoomRand& goomRand,
                        const std::string& resourcesDirectory,
                        const CreateZoomInCoefficientsEffectFunc& createZoomInCoefficientsEffect);
  FilterSettingsService(const FilterSettingsService&) noexcept = delete;
  FilterSettingsService(FilterSettingsService&&) noexcept      = delete;
  virtual ~FilterSettingsService() noexcept;
  auto operator=(const FilterSettingsService&) -> FilterSettingsService& = delete;
  auto operator=(FilterSettingsService&&) -> FilterSettingsService&      = delete;

  auto Start() -> void;
  auto NewCycle() -> void;

  auto NotifyUpdatedFilterEffectsSettings() -> void;
  [[nodiscard]] auto HasFilterModeChangedSinceLastUpdate() const -> bool;

  [[nodiscard]] auto GetCurrentFilterMode() const -> ZoomFilterMode;
  [[nodiscard]] auto GetCurrentFilterModeName() const -> const std::string_view&;
  [[nodiscard]] auto GetPreviousFilterMode() const -> ZoomFilterMode;
  [[nodiscard]] auto GetPreviousFilterModeName() const -> const std::string_view&;

  [[nodiscard]] auto GetFilterSettings() const -> const ZoomFilterSettings&;
  [[nodiscard]] auto GetROVitesse() const -> const Vitesse&;
  [[nodiscard]] auto GetRWVitesse() -> Vitesse&;

  auto SetNewRandomFilter() -> void;

  auto ChangeMilieu() -> void;
  auto ResetRandomExtraEffects() -> void;
  auto TurnOffRotation() -> void;
  auto MultiplyRotation(float factor) -> void;
  auto ToggleRotationDirection() -> void;

  auto SetTranLerpIncrement(uint32_t value) -> void;
  auto SetDefaultTranLerpIncrement() -> void;
  auto MultiplyTranLerpIncrement(uint32_t factor) -> void;
  auto SetTranLerpToMaxSwitchMult(float value) -> void;
  auto SetTranLerpToMaxDefaultSwitchMult() -> void;

protected:
  void SetFilterMode(ZoomFilterMode filterMode);
  [[nodiscard]] auto GetFilterSettings() -> ZoomFilterSettings&;
  [[nodiscard]] auto GetPluginInfo() const -> const PluginInfo&;
  [[nodiscard]] auto GetGoomRand() const -> const UTILS::MATH::IGoomRand&;
  virtual auto SetDefaultSettings() -> void;
  virtual auto SetRandomZoomMidpoint() -> void;
  virtual auto SetFilterModeRandomViewport() -> void;
  virtual auto SetFilterModeRandomEffects() -> void;
  virtual auto SetFilterModeExtraEffects() -> void;
  virtual auto SetRandomizedExtraEffects() -> void;
  virtual auto SetWaveModeExtraEffects() -> void;
  virtual auto UpdateFilterSettingsFromExtraEffects() -> void;

private:
  const PluginInfo& m_goomInfo;
  const UTILS::MATH::IGoomRand& m_goomRand;
  const Point2dInt m_screenMidpoint;
  const std::string m_resourcesDirectory;
  std::experimental::propagate_const<std::unique_ptr<AFTER_EFFECTS::AfterEffectsStates>>
      m_randomizedAfterEffects;

  ZoomFilterMode m_filterMode             = ZoomFilterMode::NORMAL_MODE;
  ZoomFilterMode m_previousFilterMode     = ZoomFilterMode::NORMAL_MODE;
  ZoomFilterMode m_filterModeAtLastUpdate = ZoomFilterMode::NORMAL_MODE;
  auto SetRandomSettingsForNewFilterMode() -> void;

  struct ZoomFilterModeInfo
  {
    std::string_view name;
    std::shared_ptr<IZoomInCoefficientsEffect> zoomInCoefficientsEffect{};
    AFTER_EFFECTS::AfterEffectsStates::AfterEffectsProbabilities afterEffectsProbabilities;
  };
  using FilterModeEnumMap = UTILS::RuntimeEnumMap<ZoomFilterMode, ZoomFilterModeInfo>;
  FilterModeEnumMap m_filterModeData;
  [[nodiscard]] static auto GetFilterModeData(
      const UTILS::MATH::IGoomRand& goomRand,
      const std::string& resourcesDirectory,
      const CreateZoomInCoefficientsEffectFunc& createZoomInCoefficientsEffect)
      -> FilterModeEnumMap;

  static constexpr uint32_t DEFAULT_ZOOM_MID_X                        = 16;
  static constexpr uint32_t DEFAULT_ZOOM_MID_Y                        = 1;
  static constexpr Viewport DEFAULT_FILTER_VIEWPORT                   = Viewport{};
  static constexpr uint32_t DEFAULT_TRAN_LERP_INCREMENT               = 0x7fU;
  static constexpr float DEFAULT_SWITCH_MULT                          = 29.0F / 30.0F;
  static constexpr float DEFAULT_MAX_ZOOM_IN_COEFF                    = 2.01F;
  static constexpr float DEFAULT_BASE_ZOOM_IN_COEFF_FACTOR_MULTIPLIER = 1.0F;
  static constexpr float MAX_MAX_ZOOM_IN_COEFF                        = 4.01F;
  ZoomFilterSettings m_filterSettings;
  const UTILS::MATH::ConditionalWeights<ZoomFilterMode> m_weightedFilterEvents;
  [[nodiscard]] auto GetNewRandomMode() const -> ZoomFilterMode;
  [[nodiscard]] auto GetZoomInCoefficientsEffect() -> std::shared_ptr<IZoomInCoefficientsEffect>&;
  auto SetMaxZoomInCoeff() -> void;
  auto SetBaseZoomInCoeffFactorMultiplier() noexcept -> void;

  enum class ZoomMidpointEvents
  {
    BOTTOM_MID_POINT,
    TOP_MID_POINT,
    LEFT_MID_POINT,
    RIGHT_MID_POINT,
    CENTRE_MID_POINT,
    BOTTOM_LEFT_QUARTER_MID_POINT,
    TOP_LEFT_QUARTER_MID_POINT,
    BOTTOM_RIGHT_QUARTER_MID_POINT,
    TOP_RIGHT_QUARTER_MID_POINT,
    _num // unused, and marks the enum end
  };
  const UTILS::MATH::Weights<ZoomMidpointEvents> m_zoomMidpointWeights;
  [[nodiscard]] auto IsZoomMidpointInTheMiddle() const -> bool;
  auto SetAnyRandomZoomMidpoint(bool allowEdgePoints) -> void;
  [[nodiscard]] auto GetWeightRandomMidPoint(bool allowEdgePoints) const -> ZoomMidpointEvents;
  [[nodiscard]] static auto IsEdgeMidPoint(ZoomMidpointEvents midPointEvent) -> bool;
};

inline auto FilterSettingsService::GetFilterSettings() const -> const ZoomFilterSettings&
{
  return m_filterSettings;
}

inline auto FilterSettingsService::GetCurrentFilterMode() const -> ZoomFilterMode
{
  return m_filterMode;
}

inline auto FilterSettingsService::GetCurrentFilterModeName() const -> const std::string_view&
{
  return m_filterModeData[m_filterMode].name;
}

inline auto FilterSettingsService::GetPreviousFilterMode() const -> ZoomFilterMode
{
  return m_previousFilterMode;
}

inline auto FilterSettingsService::GetPreviousFilterModeName() const -> const std::string_view&
{
  return m_filterModeData[m_previousFilterMode].name;
}

inline auto FilterSettingsService::GetFilterSettings() -> ZoomFilterSettings&
{
  return m_filterSettings;
}

inline auto FilterSettingsService::GetPluginInfo() const -> const PluginInfo&
{
  return m_goomInfo;
}

inline auto FilterSettingsService::GetGoomRand() const -> const UTILS::MATH::IGoomRand&
{
  return m_goomRand;
}

inline auto FilterSettingsService::HasFilterModeChangedSinceLastUpdate() const -> bool
{
  return m_filterModeAtLastUpdate != m_filterMode;
}

inline auto FilterSettingsService::GetROVitesse() const -> const Vitesse&
{
  return m_filterSettings.filterEffectsSettings.vitesse;
}

inline auto FilterSettingsService::GetRWVitesse() -> Vitesse&
{
  m_filterSettings.filterEffectsSettingsHaveChanged = true;
  return m_filterSettings.filterEffectsSettings.vitesse;
}

inline auto FilterSettingsService::ChangeMilieu() -> void
{
  m_filterSettings.filterEffectsSettingsHaveChanged = true;
  SetMaxZoomInCoeff();
  SetBaseZoomInCoeffFactorMultiplier();
  SetRandomZoomMidpoint();
}

inline auto FilterSettingsService::SetMaxZoomInCoeff() -> void
{
  static constexpr auto MIN_SPEED_FACTOR = 0.5F;
  static constexpr auto MAX_SPEED_FACTOR = 1.0F;
  m_filterSettings.filterEffectsSettings.maxZoomInCoeff =
      m_goomRand.GetRandInRange(MIN_SPEED_FACTOR, MAX_SPEED_FACTOR) * MAX_MAX_ZOOM_IN_COEFF;
}

inline auto FilterSettingsService::SetFilterMode(const ZoomFilterMode filterMode) -> void
{
  m_filterSettings.filterEffectsSettingsHaveChanged = true;

  m_previousFilterMode = m_filterMode;
  m_filterMode         = filterMode;

  SetRandomSettingsForNewFilterMode();
}

inline auto FilterSettingsService::SetNewRandomFilter() -> void
{
  m_filterSettings.filterEffectsSettingsHaveChanged = true;

  m_previousFilterMode = m_filterMode;
  m_filterMode         = GetNewRandomMode();

  SetRandomSettingsForNewFilterMode();
}

inline auto FilterSettingsService::SetRandomSettingsForNewFilterMode() -> void
{
  SetDefaultSettings();
  SetRandomZoomMidpoint();
  SetFilterModeRandomEffects();
  SetFilterModeRandomViewport();
  SetFilterModeExtraEffects();
  UpdateFilterSettingsFromExtraEffects();
}

inline auto FilterSettingsService::TurnOffRotation() -> void
{
  if (not m_filterSettings.filterEffectsSettings.afterEffectsSettings
              .active[AFTER_EFFECTS::AfterEffectsTypes::ROTATION])
  {
    return;
  }
  m_filterSettings.filterEffectsSettingsHaveChanged = true;
  m_filterSettings.filterEffectsSettings.afterEffectsSettings
      .active[AFTER_EFFECTS::AfterEffectsTypes::ROTATION] = false;
}

inline auto FilterSettingsService::MultiplyRotation(const float factor) -> void
{
  if (not m_filterSettings.filterEffectsSettings.afterEffectsSettings
              .active[AFTER_EFFECTS::AfterEffectsTypes::ROTATION])
  {
    return;
  }
  m_filterSettings.filterEffectsSettingsHaveChanged = true;
  m_filterSettings.filterEffectsSettings.afterEffectsSettings.rotationAdjustments.SetMultiplyFactor(
      factor, AFTER_EFFECTS::RotationAdjustments::AdjustmentType::INSTEAD_OF_RANDOM);
}

inline auto FilterSettingsService::ToggleRotationDirection() -> void
{
  if (not m_filterSettings.filterEffectsSettings.afterEffectsSettings
              .active[AFTER_EFFECTS::AfterEffectsTypes::ROTATION])
  {
    return;
  }

  m_filterSettings.filterEffectsSettingsHaveChanged = true;
  m_filterSettings.filterEffectsSettings.afterEffectsSettings.rotationAdjustments.Toggle(
      AFTER_EFFECTS::RotationAdjustments::AdjustmentType::INSTEAD_OF_RANDOM);
}

inline auto FilterSettingsService::SetTranLerpIncrement(const uint32_t value) -> void
{
  m_filterSettings.filterBufferSettings.tranLerpIncrement = value;
}

inline auto FilterSettingsService::SetDefaultTranLerpIncrement() -> void
{
  SetTranLerpIncrement(DEFAULT_TRAN_LERP_INCREMENT);
}

inline auto FilterSettingsService::MultiplyTranLerpIncrement(const uint32_t factor) -> void
{
  m_filterSettings.filterBufferSettings.tranLerpIncrement *= factor;
}

inline auto FilterSettingsService::SetTranLerpToMaxSwitchMult(const float value) -> void
{
  m_filterSettings.filterBufferSettings.tranLerpToMaxSwitchMult = value;
}

inline auto FilterSettingsService::SetTranLerpToMaxDefaultSwitchMult() -> void
{
  SetTranLerpToMaxSwitchMult(DEFAULT_SWITCH_MULT);
}

} // namespace GOOM::FILTER_FX
