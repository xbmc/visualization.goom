#pragma once

#include "spimpl.h"
#include "utils/name_value_pairs.h"

#include <cstdint>
#include <memory>

namespace GOOM
{

namespace UTILS
{
class Parallel;
}

struct FXBuffSettings;
class PixelBuffer;
class PluginInfo;

namespace FILTER_FX
{

class FilterBufferColorInfo;
class FilterBuffersService;
class FilterColorsService;
struct ZoomFilterBufferSettings;
struct ZoomFilterEffectsSettings;

class ZoomFilterFx
{
public:
  ZoomFilterFx() noexcept = delete;
  ZoomFilterFx(UTILS::Parallel& parallel,
               const PluginInfo& goomInfo,
               std::unique_ptr<FilterBuffersService> filterBuffersService,
               std::unique_ptr<FilterColorsService> filterColorsService) noexcept;

  auto SetBuffSettings(const FXBuffSettings& settings) noexcept -> void;

  auto Start() noexcept -> void;
  auto Finish() noexcept -> void;

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

  [[nodiscard]] auto GetNameValueParams() const noexcept -> UTILS::NameValuePairs;

protected:
  [[nodiscard]] auto GetFilterBuffersService() noexcept -> FilterBuffersService&;
  auto CZoom(const PixelBuffer& srceBuff, PixelBuffer& destBuff) noexcept -> void;

private:
  class ZoomFilterImpl;
  spimpl::unique_impl_ptr<ZoomFilterImpl> m_pimpl;
};

} // namespace FILTER_FX
} // namespace GOOM
