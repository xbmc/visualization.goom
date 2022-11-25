#pragma once

#include "utils/name_value_pairs.h"

#include <string>

namespace GOOM::FILTER_FX
{

class NormalizedCoords;
struct ZoomFilterEffectsSettings;

class IZoomVector
{
public:
  IZoomVector() noexcept                             = default;
  IZoomVector(const IZoomVector&) noexcept           = delete;
  IZoomVector(IZoomVector&&) noexcept                = delete;
  virtual ~IZoomVector() noexcept                    = default;
  auto operator=(const IZoomVector&) -> IZoomVector& = delete;
  auto operator=(IZoomVector&&) -> IZoomVector&      = delete;

  virtual auto SetFilterSettings(const ZoomFilterEffectsSettings& filterEffectsSettings) noexcept
      -> void = 0;

  virtual auto GetZoomInPoint(const NormalizedCoords& coords,
                              const NormalizedCoords& filterViewportCoords) const noexcept
      -> NormalizedCoords = 0;

  [[nodiscard]] virtual auto GetNameValueParams(const std::string& paramGroup) const noexcept
      -> UTILS::NameValuePairs = 0;
};

} // namespace GOOM::FILTER_FX
