#pragma once

#include "draw/goom_draw.h"
#include "filter_fx/filter_buffer_color_info.h"
#include "filter_fx/filter_settings.h"
#include "filter_fx/zoom_filter_fx.h"
#include "goom_config.h"
#include "goom_state_handler.h"
#include "goom_states.h"
#include "spimpl.h"
#include "utils/adaptive_exposure.h"
#include "utils/math/misc.h"
#include "utils/propagate_const.h"
#include "utils/stopwatch.h"
#include "visual_fx_color_maps.h"

#include <functional>
#include <memory>
#include <string_view>
#include <unordered_set>

namespace GOOM
{
class AudioSamples;
class PluginInfo;
class PixelBuffer;

namespace UTILS
{
class Parallel;
namespace GRAPHICS
{
class SmallImageBitmaps;
}
namespace MATH
{
class IGoomRand;
}
} // namespace UTILS

namespace VISUAL_FX
{
class FxHelper;
}

namespace FILTER_FX
{
class FilterBuffersService;
class FilterColorsService;
struct ZoomFilterSettings;
}

namespace CONTROL
{
class AllStandardVisualFx;

class GoomAllVisualFx
{
public:
  GoomAllVisualFx() noexcept = delete;
  GoomAllVisualFx(UTILS::Parallel& parallel,
                  const VISUAL_FX::FxHelper& fxHelper,
                  const UTILS::GRAPHICS::SmallImageBitmaps& smallBitmaps,
                  const std::string& resourcesDirectory,
                  IGoomStateHandler& goomStateHandler,
                  std::unique_ptr<FILTER_FX::FilterBuffersService> filterBuffersService,
                  std::unique_ptr<FILTER_FX::FilterColorsService> filterColorsService) noexcept;
  GoomAllVisualFx(const GoomAllVisualFx&) noexcept = delete;
  GoomAllVisualFx(GoomAllVisualFx&&) noexcept      = delete;
  ~GoomAllVisualFx() noexcept;
  auto operator=(const GoomAllVisualFx&) noexcept -> GoomAllVisualFx& = delete;
  auto operator=(GoomAllVisualFx&&) noexcept -> GoomAllVisualFx&      = delete;

  void Start();
  void Finish();

  auto SetAllowMultiThreadedStates(bool val) -> void;

  [[nodiscard]] auto GetZoomFilterFx() const -> const FILTER_FX::ZoomFilterFx&;

  void SetNextState();
  [[nodiscard]] auto GetCurrentState() const -> GoomStates;
  [[nodiscard]] auto GetCurrentStateName() const -> std::string_view;

  void SetSingleBufferDots(bool value);

  void StartExposureControl();
  [[nodiscard]] auto GetCurrentExposure() const -> float;
  [[nodiscard]] auto GetLastShaderEffects() const -> const GoomShaderEffects&;

  using ResetDrawBuffSettingsFunc = std::function<void(const FXBuffSettings& settings)>;
  void SetResetDrawBuffSettingsFunc(const ResetDrawBuffSettingsFunc& func);

  void ChangeAllFxColorMaps();
  void ChangeDrawPixelBlend();
  void RefreshAllFx();

  void ApplyCurrentStateToSingleBuffer();
  void ApplyCurrentStateToMultipleBuffers(const AudioSamples& soundData);
  auto ApplyEndEffectIfNearEnd(const UTILS::Stopwatch::TimeValues& timeValues) -> void;

  void UpdateFilterSettings(const FILTER_FX::ZoomFilterSettings& filterSettings);
  void ApplyZoom(const PixelBuffer& srceBuff, PixelBuffer& destBuff);

  [[nodiscard]] auto GetCurrentColorMapsNames() const -> std::unordered_set<std::string>;
  [[nodiscard]] auto GetZoomFilterFxNameValueParams() const -> UTILS::NameValuePairs;

private:
  DRAW::IGoomDraw& m_goomDraw;
  const UTILS::MATH::IGoomRand& m_goomRand;
  spimpl::unique_impl_ptr<AllStandardVisualFx> m_allStandardVisualFx;
  std::experimental::propagate_const<std::unique_ptr<FILTER_FX::ZoomFilterFx>> m_zoomFilterFx;

  IGoomStateHandler& m_goomStateHandler;
  bool m_allowMultiThreadedStates = true;
  void ChangeState();
  void PostStateUpdate(const std::unordered_set<GoomDrawables>& oldGoomDrawables);
  std::unordered_set<GoomDrawables> m_currentGoomDrawables{};

  ResetDrawBuffSettingsFunc m_resetDrawBuffSettings{};
  void ResetCurrentDrawBuffSettings(GoomDrawables fx);
  [[nodiscard]] auto GetCurrentBuffSettings(GoomDrawables fx) const -> FXBuffSettings;

  VisualFxColorMaps m_visualFxColorMaps{m_goomRand};
  UTILS::AdaptiveExposure m_adaptiveExposure{};
  bool m_doExposureControl = false;
  void UpdateZoomFilterLuminance();
  [[nodiscard]] auto GetCurrentBufferAverageLuminance() noexcept -> float;

  [[nodiscard]] static auto GetReverseColorAddBlendPixelPixelFunc()
      -> DRAW::IGoomDraw::BlendPixelFunc;
  [[nodiscard]] static auto GetSameLumaBlendPixelFunc() -> DRAW::IGoomDraw::BlendPixelFunc;
  [[nodiscard]] static auto GetSameLumaMixBlendPixelFunc() -> DRAW::IGoomDraw::BlendPixelFunc;
};

inline auto GoomAllVisualFx::SetAllowMultiThreadedStates(const bool val) -> void
{
  m_allowMultiThreadedStates = val;
}

inline auto GoomAllVisualFx::GetZoomFilterFx() const -> const FILTER_FX::ZoomFilterFx&
{
  return *m_zoomFilterFx;
}

inline void GoomAllVisualFx::SetNextState()
{
  ChangeState();
  ChangeAllFxColorMaps();
  ChangeDrawPixelBlend();
  PostStateUpdate(m_currentGoomDrawables);
}

inline void GoomAllVisualFx::SetResetDrawBuffSettingsFunc(const ResetDrawBuffSettingsFunc& func)
{
  m_resetDrawBuffSettings = func;
}

inline void GoomAllVisualFx::ApplyZoom(const PixelBuffer& srceBuff, PixelBuffer& destBuff)
{
  m_zoomFilterFx->ZoomFilterFastRgb(srceBuff, destBuff);

  UpdateZoomFilterLuminance();
}

inline void GoomAllVisualFx::UpdateZoomFilterLuminance()
{
  const auto averageLuminanceToUse = GetCurrentBufferAverageLuminance();
  if (averageLuminanceToUse < UTILS::MATH::SMALL_FLOAT)
  {
    // No point trying to handle zero luminance.
    return;
  }

  m_adaptiveExposure.UpdateAverageLuminance(averageLuminanceToUse);

  if (m_doExposureControl)
  {
    m_zoomFilterFx->SetZoomFilterBrightness(m_adaptiveExposure.GetCurrentExposure());
  }
}

inline auto GoomAllVisualFx::GetCurrentBufferAverageLuminance() noexcept -> float
{
  m_zoomFilterFx->GetLastFilterBufferColorInfo().CalculateLuminances();

  const auto& filterBufferColorInfo = m_zoomFilterFx->GetLastFilterBufferColorInfo();

  const auto maxRegionAverageLuminance = filterBufferColorInfo.GetMaxRegionAverageLuminance();
  if (maxRegionAverageLuminance < UTILS::MATH::SMALL_FLOAT)
  {
    return 0.0F;
  }

  const auto zoomPointRegionAverageLuminance =
      filterBufferColorInfo.GetRegionAverageLuminanceAtPoint(
          m_zoomFilterFx->GetFilterEffectsSettings().zoomMidpoint);
  static constexpr auto LUMINANCE_MIX = 0.5F;

  return STD20::lerp(zoomPointRegionAverageLuminance, maxRegionAverageLuminance, LUMINANCE_MIX);
}

inline auto GoomAllVisualFx::GetCurrentExposure() const -> float
{
  return m_adaptiveExposure.GetCurrentExposure();
}

inline auto GoomAllVisualFx::GetCurrentState() const -> GoomStates
{
  return m_goomStateHandler.GetCurrentState();
}

inline auto GoomAllVisualFx::GetCurrentStateName() const -> std::string_view
{
  return GoomStateInfo::GetStateInfo(m_goomStateHandler.GetCurrentState()).name;
}

} // namespace CONTROL
} // namespace GOOM
