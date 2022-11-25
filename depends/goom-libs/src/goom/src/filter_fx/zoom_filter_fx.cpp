/* filter.c version 0.7
 * contient les filtres applicable a un buffer
 * creation : 01/10/2000
 *  -ajout de sinFilter()
 *  -ajout de zoomFilter()
 *  -copie de zoomFilter() en zoomFilterRGB(), gerant les 3 couleurs
 *  -optimisation de sinFilter (utilisant une table de sin)
 *  -asm
 *  -optimisation de la procedure de generation du buffer de transformation
 *     la vitesse est maintenant comprise dans [0..128] au lieu de [0..100]
 *
 *  - converted to C++17 2021-02-01 (glk)
 */

#include "zoom_filter_fx.h"

//#undef NO_LOGGING

#include "filter_buffer_color_info.h"
#include "filter_buffers_service.h"
#include "filter_colors_service.h"
#include "goom_config.h"
#include "goom_graphic.h"
#include "goom_plugin_info.h"
#include "goom_types.h"
#include "logging.h"
#include "spimpl.h"
#include "utils/name_value_pairs.h"
#include "utils/parallel_utils.h"
#include "utils/propagate_const.h"

#include <array>
#include <cstdint>
#include <memory>


namespace GOOM::FILTER_FX
{

using std::experimental::propagate_const;
using UTILS::GetPair;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::MoveNameValuePairs;
using UTILS::NameValuePairs;
using UTILS::Parallel;

class ZoomFilterFx::ZoomFilterImpl
{
public:
  ZoomFilterImpl() noexcept = delete;
  ZoomFilterImpl(Parallel& parallel,
                 const PluginInfo& goomInfo,
                 std::unique_ptr<FilterBuffersService> filterBuffersService,
                 std::unique_ptr<FilterColorsService> filterColorsService) noexcept;

  auto SetBuffSettings(const FXBuffSettings& settings) noexcept -> void;

  auto Start() noexcept -> void;

  [[nodiscard]] auto GetTranLerpFactor() const noexcept -> uint32_t;

  [[nodiscard]] auto GetFilterEffectsSettings() const noexcept -> const ZoomFilterEffectsSettings&;
  auto UpdateFilterEffectsSettings(const ZoomFilterEffectsSettings& filterEffectsSettings) noexcept
      -> void;
  auto UpdateFilterBufferSettings(const ZoomFilterBufferSettings& filterBufferSettings) noexcept
      -> void;
  auto UpdateFilterColorSettings(bool blockyWavy) noexcept -> void;

  auto ZoomFilterFastRgb(const PixelBuffer& srceBuff, PixelBuffer& destBuff) noexcept -> void;
  auto SetZoomFilterBrightness(float brightness) noexcept -> void;
  [[nodiscard]] auto GetLastFilterBufferColorInfo() const noexcept -> const FilterBufferColorInfo&;
  [[nodiscard]] auto GetLastFilterBufferColorInfo() noexcept -> FilterBufferColorInfo&;

  [[nodiscard]] auto GetNameValueParams() const noexcept -> NameValuePairs;

  [[nodiscard]] auto GetFilterBuffersService() noexcept -> FilterBuffersService&;

  auto CZoom(const PixelBuffer& srceBuff, PixelBuffer& destBuff) noexcept -> void;

private:
  const Dimensions m_dimensions;
  Parallel& m_parallel;

  propagate_const<std::unique_ptr<FilterBuffersService>> m_filterBuffersService;
  propagate_const<std::unique_ptr<FilterColorsService>> m_filterColorsService;

  uint64_t m_updateNum = 0;

  FilterBufferColorInfo m_filterBufferColorInfo{m_dimensions};
};

ZoomFilterFx::ZoomFilterFx(Parallel& parallel,
                           const PluginInfo& goomInfo,
                           std::unique_ptr<FilterBuffersService> filterBuffersService,
                           std::unique_ptr<FilterColorsService> filterColorsService) noexcept
  : m_pimpl{spimpl::make_unique_impl<ZoomFilterImpl>(
        parallel, goomInfo, std::move(filterBuffersService), std::move(filterColorsService))}
{
}

auto ZoomFilterFx::SetBuffSettings(const FXBuffSettings& settings) noexcept -> void
{
  m_pimpl->SetBuffSettings(settings);
}

auto ZoomFilterFx::GetNameValueParams() const noexcept -> NameValuePairs
{
  return m_pimpl->GetNameValueParams();
}

auto ZoomFilterFx::GetFilterBuffersService() noexcept -> FilterBuffersService&
{
  return m_pimpl->GetFilterBuffersService();
}

auto ZoomFilterFx::CZoom(const PixelBuffer& srceBuff, PixelBuffer& destBuff) noexcept -> void
{
  m_pimpl->CZoom(srceBuff, destBuff);
}

auto ZoomFilterFx::Start() noexcept -> void
{
  m_pimpl->Start();
}

auto ZoomFilterFx::Finish() noexcept -> void
{
  // No finish actions required
}

auto ZoomFilterFx::GetTranLerpFactor() const noexcept -> uint32_t
{
  return m_pimpl->GetTranLerpFactor();
}

auto ZoomFilterFx::GetFilterEffectsSettings() const noexcept -> const ZoomFilterEffectsSettings&
{
  return m_pimpl->GetFilterEffectsSettings();
}

auto ZoomFilterFx::UpdateFilterEffectsSettings(
    const ZoomFilterEffectsSettings& filterEffectsSettings) noexcept -> void
{
  m_pimpl->UpdateFilterEffectsSettings(filterEffectsSettings);
}

auto ZoomFilterFx::UpdateFilterBufferSettings(
    const ZoomFilterBufferSettings& filterBufferSettings) noexcept -> void
{
  m_pimpl->UpdateFilterBufferSettings(filterBufferSettings);
}

auto ZoomFilterFx::UpdateFilterColorSettings(const bool blockyWavy) noexcept -> void
{
  m_pimpl->UpdateFilterColorSettings(blockyWavy);
}

auto ZoomFilterFx::ZoomFilterFastRgb(const PixelBuffer& srceBuff, PixelBuffer& destBuff) noexcept
    -> void
{
  m_pimpl->ZoomFilterFastRgb(srceBuff, destBuff);
}

auto ZoomFilterFx::SetZoomFilterBrightness(const float brightness) noexcept -> void
{
  m_pimpl->SetZoomFilterBrightness(brightness);
}

auto ZoomFilterFx::GetLastFilterBufferColorInfo() const noexcept -> const FilterBufferColorInfo&
{
  return m_pimpl->GetLastFilterBufferColorInfo();
}

auto ZoomFilterFx::GetLastFilterBufferColorInfo() noexcept -> FilterBufferColorInfo&
{
  return m_pimpl->GetLastFilterBufferColorInfo();
}

ZoomFilterFx::ZoomFilterImpl::ZoomFilterImpl(
    Parallel& parallel,
    const PluginInfo& goomInfo,
    std::unique_ptr<FilterBuffersService> filterBuffersService,
    std::unique_ptr<FilterColorsService> filterColorsService) noexcept
  : m_dimensions{goomInfo.GetScreenDimensions()},
    m_parallel{parallel},
    m_filterBuffersService{std::move(filterBuffersService)},
    m_filterColorsService{std::move(filterColorsService)}
{
}

inline auto ZoomFilterFx::ZoomFilterImpl::SetBuffSettings(const FXBuffSettings& settings) noexcept
    -> void
{
  m_filterColorsService->SetBuffSettings(settings);
}

inline auto ZoomFilterFx::ZoomFilterImpl::GetTranLerpFactor() const noexcept -> uint32_t
{
  return m_filterBuffersService->GetTranLerpFactor();
}

inline auto ZoomFilterFx::ZoomFilterImpl::GetFilterEffectsSettings() const noexcept
    -> const ZoomFilterEffectsSettings&
{
  return m_filterBuffersService->GetCurrentFilterEffectsSettings();
}

inline auto ZoomFilterFx::ZoomFilterImpl::UpdateFilterEffectsSettings(
    const ZoomFilterEffectsSettings& filterEffectsSettings) noexcept -> void
{
  m_filterBuffersService->SetFilterEffectsSettings(filterEffectsSettings);
}

inline auto ZoomFilterFx::ZoomFilterImpl::UpdateFilterColorSettings(const bool blockyWavy) noexcept
    -> void
{
  m_filterColorsService->SetBlockyWavy(blockyWavy);
}

inline auto ZoomFilterFx::ZoomFilterImpl::UpdateFilterBufferSettings(
    const ZoomFilterBufferSettings& filterBufferSettings) noexcept -> void
{
  m_filterBuffersService->SetFilterBufferSettings(filterBufferSettings);
}

auto ZoomFilterFx::ZoomFilterImpl::GetNameValueParams() const noexcept -> NameValuePairs
{
  static constexpr auto* PARAM_GROUP = "ZoomFilterFx";

  auto nameValuePairs = NameValuePairs{GetPair(PARAM_GROUP, "tranLerpFactor", GetTranLerpFactor())};

  MoveNameValuePairs(m_filterColorsService->GetNameValueParams(PARAM_GROUP), nameValuePairs);
  MoveNameValuePairs(m_filterBuffersService->GetNameValueParams(PARAM_GROUP), nameValuePairs);

  return nameValuePairs;
}

inline auto ZoomFilterFx::ZoomFilterImpl::GetFilterBuffersService() noexcept
    -> FilterBuffersService&
{
  return *m_filterBuffersService;
}

inline auto ZoomFilterFx::ZoomFilterImpl::Start() noexcept -> void
{
  m_filterBuffersService->Start();
}

/**
 * Main work for the dynamic displacement map.
 *
 * Reads data from pix1, write to pix2.
 *
 * Useful data for this FX are stored in ZoomFilterData.
 *
 * If you think that this is a strange function name, let me say that a long time ago,
 *  there has been a slow version and a gray-level only one. Then came these function,
 *  fast and working in RGB colorspace ! nice but it only was applying a zoom to the image.
 *  So that is why you have this name, for the nostalgia of the first days of goom
 *  when it was just a tiny program writen in Turbo Pascal on my i486...
 */
inline auto ZoomFilterFx::ZoomFilterImpl::ZoomFilterFastRgb(const PixelBuffer& srceBuff,
                                                            PixelBuffer& destBuff) noexcept -> void
{
  ++m_updateNum;

  m_filterBuffersService->UpdateTranBuffers();

  CZoom(srceBuff, destBuff);
}

inline auto ZoomFilterFx::ZoomFilterImpl::SetZoomFilterBrightness(const float brightness) noexcept
    -> void
{
  m_filterColorsService->SetBrightness(brightness);
}

inline auto ZoomFilterFx::ZoomFilterImpl::GetLastFilterBufferColorInfo() const noexcept
    -> const FilterBufferColorInfo&
{
  return m_filterBufferColorInfo;
}

inline auto ZoomFilterFx::ZoomFilterImpl::GetLastFilterBufferColorInfo() noexcept
    -> FilterBufferColorInfo&
{
  return m_filterBufferColorInfo;
}

auto ZoomFilterFx::ZoomFilterImpl::CZoom(const PixelBuffer& srceBuff,
                                         PixelBuffer& destBuff) noexcept -> void
{
  const auto setDestPixelRow = [this, &srceBuff, &destBuff](const size_t destY) noexcept
  {
    const auto [destRowBegin, destRowEnd] = destBuff.GetRowIter(destY);

    auto& filterBufferRowColorInfo = m_filterBufferColorInfo.GetRow(destY);

    filterBufferRowColorInfo.Reset();
    auto destPos = m_dimensions.GetWidth() * static_cast<uint32_t>(destY);

    for (auto destRowBuff = destRowBegin; destRowBuff != destRowEnd; ++destRowBuff)
    {
      const auto srcePointInfo = m_filterBuffersService->GetSourcePointInfo(destPos);
      const auto srcePointNeighbours =
          srceBuff.Get4RHBNeighbours(srcePointInfo.screenPoint.x, srcePointInfo.screenPoint.y);
      const auto newColor = m_filterColorsService->GetNewColor(srcePointInfo, srcePointNeighbours);

      filterBufferRowColorInfo.UpdateColor(newColor);
      *destRowBuff = newColor;

      filterBufferRowColorInfo.NextX();
      ++destPos;
    }
  };

  m_parallel.ForLoop(m_dimensions.GetHeight(), setDestPixelRow);
}

} // namespace GOOM::FILTER_FX
