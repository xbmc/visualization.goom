#pragma once

#include "filter_fx/normalized_coords.h"
#include "filter_fx/zoom_in_coefficients_effect.h"
#include "point2d.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

class UniformZoomInCoefficientsEffect : public IZoomInCoefficientsEffect
{
public:
  UniformZoomInCoefficientsEffect() noexcept = default;

  auto SetRandomParams() noexcept -> void override;

  [[nodiscard]] auto GetZoomInCoefficients(const NormalizedCoords& coords,
                                           float sqDistFromZero) const noexcept
      -> Point2dFlt override;

  [[nodiscard]] auto GetZoomInCoefficientsEffectNameValueParams() const noexcept
      -> GOOM::UTILS::NameValuePairs override;
};

inline auto UniformZoomInCoefficientsEffect::GetZoomInCoefficients(
    [[maybe_unused]] const NormalizedCoords& coords,
    [[maybe_unused]] const float sqDistFromZero) const noexcept -> Point2dFlt
{
  return GetBaseZoomInCoeffs();
}

inline auto UniformZoomInCoefficientsEffect::SetRandomParams() noexcept -> void
{
  // do nothing
}

inline auto UniformZoomInCoefficientsEffect::GetZoomInCoefficientsEffectNameValueParams()
    const noexcept -> GOOM::UTILS::NameValuePairs
{
  return GOOM::UTILS::NameValuePairs();
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
