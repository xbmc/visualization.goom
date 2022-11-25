#pragma once

#include "filter_effects/zoom_vector_effects.h"
#include "normalized_coords.h"
#include "utils/name_value_pairs.h"
#include "zoom_vector.h"

#include <cstdint>
#include <memory>

namespace GOOM::UTILS::MATH
{
class IGoomRand;
}

namespace GOOM::FILTER_FX
{

class FilterZoomVector : public IZoomVector
{
public:
  FilterZoomVector(uint32_t screenWidth,
                   const std::string& resourcesDirectory,
                   const UTILS::MATH::IGoomRand& goomRand,
                   const NormalizedCoordsConverter& normalizedCoordsConverter,
                   const FILTER_EFFECTS::ZoomVectorEffects::GetAfterEffectsFunc& getAfterEffects =
                       FILTER_EFFECTS::ZoomVectorEffects::GetStandardAfterEffects) noexcept;

  auto SetFilterSettings(const ZoomFilterEffectsSettings& filterEffectsSettings) noexcept
      -> void override;

  [[nodiscard]] auto GetZoomInPoint(const NormalizedCoords& coords,
                                    const NormalizedCoords& filterViewportCoords) const noexcept
      -> NormalizedCoords override;

  [[nodiscard]] auto GetNameValueParams(const std::string& paramGroup) const noexcept
      -> UTILS::NameValuePairs override;

private:
  FILTER_EFFECTS::ZoomVectorEffects m_zoomVectorEffects;
};

} // namespace GOOM::FILTER_FX
