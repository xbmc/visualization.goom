#pragma once

#include "filter_fx/common_types.h"
#include "filter_fx/normalized_coords.h"
#include "filter_fx/zoom_in_coefficients_effect.h"
#include "point2d.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

class YOnly : public IZoomInCoefficientsEffect
{
public:
  explicit YOnly(const UTILS::MATH::IGoomRand& goomRand) noexcept;

  auto SetRandomParams() noexcept -> void override;

  [[nodiscard]] auto GetZoomInCoefficients(const NormalizedCoords& coords,
                                           float sqDistFromZero) const noexcept
      -> Point2dFlt override;

  [[nodiscard]] auto GetZoomInCoefficientsEffectNameValueParams() const noexcept
      -> UTILS::NameValuePairs override;

  enum class YOnlyEffect
  {
    NONE,
    X_SIN_Y_SIN,
    X_SIN_Y_COS,
    X_COS_Y_SIN,
    X_COS_Y_COS,
    _num // unused, and marks the enum end
  };
  struct YOnlyXYEffect
  {
    YOnlyEffect xEffect;
    YOnlyEffect yEffect;
  };
  struct Params
  {
    YOnlyXYEffect xyEffect;
    FrequencyFactor frequencyFactor;
    Amplitude amplitude;
  };
  [[nodiscard]] auto GetParams() const noexcept -> const Params&;

protected:
  auto SetParams(const Params& params) noexcept -> void;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;
  Params m_params;
  [[nodiscard]] auto GetYOnlyZoomInMultiplier(YOnlyEffect effect,
                                              const NormalizedCoords& coords) const noexcept
      -> float;
};

inline auto YOnly::GetZoomInCoefficients(const NormalizedCoords& coords,
                                         [[maybe_unused]] const float sqDistFromZero) const noexcept
    -> Point2dFlt
{
  const auto xZoomInCoeff = GetBaseZoomInCoeffs().x * m_params.amplitude.x *
                            GetYOnlyZoomInMultiplier(m_params.xyEffect.xEffect, coords);
  if (m_params.xyEffect.yEffect == YOnlyEffect::NONE)
  {
    return {xZoomInCoeff, xZoomInCoeff};
  }

  return {xZoomInCoeff,
          GetBaseZoomInCoeffs().y * m_params.amplitude.y *
              GetYOnlyZoomInMultiplier(m_params.xyEffect.yEffect, coords)};
}

inline auto YOnly::GetParams() const noexcept -> const Params&
{
  return m_params;
}

inline auto YOnly::SetParams(const Params& params) noexcept -> void
{
  m_params = params;
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
