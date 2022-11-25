#include "filter_buffers_service.h"

//#undef NO_LOGGING

#include "filter_buffers.h"
#include "filter_settings.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "logging.h"
#include "normalized_coords.h"
#include "utils/math/misc.h"
#include "utils/name_value_pairs.h"
#include "utils/parallel_utils.h"
#include "zoom_in_coefficients_effect.h"
#include "zoom_vector.h"

#include <cstdint>

namespace GOOM::FILTER_FX
{

using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::NameValuePairs;
using UTILS::Parallel;
using UTILS::MATH::FloatsEqual;

FilterBuffersService::FilterBuffersService(
    Parallel& parallel,
    const PluginInfo& goomInfo,
    const NormalizedCoordsConverter& normalizedCoordsConverter,
    std::unique_ptr<IZoomVector> zoomVector) noexcept
  : m_zoomVector{std::move(zoomVector)},
    m_filterBuffers{
        parallel,
        goomInfo,
        normalizedCoordsConverter,
        [this](const NormalizedCoords& normalizedCoords,
               const NormalizedCoords& normalizedFilterViewportCoords)
        { return m_zoomVector->GetZoomInPoint(normalizedCoords, normalizedFilterViewportCoords); }}
{
}

auto FilterBuffersService::SetFilterBufferSettings(
    const ZoomFilterBufferSettings& filterBufferSettings) noexcept -> void
{
  m_filterBuffers.SetFilterViewport(filterBufferSettings.filterEffectViewport);

  UpdateTranLerpFactor(filterBufferSettings.tranLerpIncrement,
                       filterBufferSettings.tranLerpToMaxSwitchMult);
}

auto FilterBuffersService::SetFilterEffectsSettings(
    const ZoomFilterEffectsSettings& filterEffectsSettings) noexcept -> void
{
  m_nextFilterEffectsSettings    = filterEffectsSettings;
  m_pendingFilterEffectsSettings = true;
}

auto FilterBuffersService::GetNameValueParams(const std::string& paramGroup) const noexcept
    -> NameValuePairs
{
  return m_zoomVector->GetNameValueParams(paramGroup);
}

auto FilterBuffersService::Start() noexcept -> void
{
  m_currentFilterEffectsSettings = m_nextFilterEffectsSettings;
  Expects(m_currentFilterEffectsSettings.zoomInCoefficientsEffect != nullptr);

  UpdateFilterEffectsSettings();

  m_filterBuffers.Start();
}

inline auto FilterBuffersService::UpdateFilterEffectsSettings() noexcept -> void
{
  UpdateZoomVectorFilterEffectsSettings();

  m_filterBuffers.SetBuffMidpoint(m_currentFilterEffectsSettings.zoomMidpoint);
  m_filterBuffers.NotifyFilterSettingsHaveChanged();
}

inline auto FilterBuffersService::UpdateZoomVectorFilterEffectsSettings() noexcept -> void
{
  m_zoomVector->SetFilterSettings(m_currentFilterEffectsSettings);

  m_currentFilterEffectsSettings.afterEffectsSettings.rotationAdjustments.Reset();
}

auto FilterBuffersService::UpdateTranBuffers() noexcept -> void
{
  m_filterBuffers.UpdateTranBuffers();

  if (AreStartingFreshTranBuffers())
  {
    StartFreshTranBuffers();
  }
}

inline auto FilterBuffersService::AreStartingFreshTranBuffers() const noexcept -> bool
{
  return m_filterBuffers.GetTranBuffersState() ==
         ZoomFilterBuffers::TranBuffersState::START_FRESH_TRAN_BUFFERS;
}

auto FilterBuffersService::StartFreshTranBuffers() noexcept -> void
{
  // Don't start making new stripes until filter settings change.
  if (!m_pendingFilterEffectsSettings)
  {
    return;
  }

  m_currentFilterEffectsSettings = m_nextFilterEffectsSettings;

  UpdateFilterEffectsSettings();

  m_pendingFilterEffectsSettings = false;
}

inline auto FilterBuffersService::UpdateTranLerpFactor(const uint32_t tranLerpIncrement,
                                                       const float tranLerpToMaxSwitchMult) noexcept
    -> void
{
  auto tranLerpFactor = m_filterBuffers.GetTranLerpFactor();

  if (tranLerpIncrement != 0U)
  {
    tranLerpFactor =
        std::min(tranLerpFactor + tranLerpIncrement, ZoomFilterBuffers::GetMaxTranLerpFactor());
  }

  if (not FloatsEqual(tranLerpToMaxSwitchMult, 1.0F))
  {
    tranLerpFactor = STD20::lerp(
        ZoomFilterBuffers::GetMaxTranLerpFactor(), tranLerpFactor, tranLerpToMaxSwitchMult);
  }

  m_filterBuffers.SetTranLerpFactor(tranLerpFactor);
}

} // namespace GOOM::FILTER_FX
