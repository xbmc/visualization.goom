#pragma once

#include "filter_fx/common_types.h"
#include "filter_fx/normalized_coords.h"
#include "filter_fx/zoom_in_coefficients_effect.h"
#include "point2d.h"
#include "utils/math/goom_rand_base.h"
#include "utils/name_value_pairs.h"

#include <complex>

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

class ExpReciprocal : public IZoomInCoefficientsEffect
{
public:
  explicit ExpReciprocal(const UTILS::MATH::IGoomRand& goomRand) noexcept;

  auto SetRandomParams() noexcept -> void override;
  [[nodiscard]] auto GetZoomInCoefficientsViewport() const noexcept -> Viewport override;

  [[nodiscard]] auto GetZoomInCoefficients(const NormalizedCoords& coords,
                                           float sqDistFromZero) const noexcept
      -> Point2dFlt override;

  [[nodiscard]] auto GetZoomInCoefficientsEffectNameValueParams() const noexcept
      -> UTILS::NameValuePairs override;

  struct Params
  {
    Viewport viewport;
    Amplitude amplitude;
    bool noInverseSquare;
    std::complex<float> magnifyAndRotate;
    float reciprocalExponent;
    bool useModulatorContours;
    float modulatorPeriod;
  };
  [[nodiscard]] auto GetParams() const noexcept -> const Params&;

protected:
  auto SetParams(const Params& params) noexcept -> void;

private:
  const UTILS::MATH::IGoomRand& m_goomRand;
  Params m_params;
  using FltCalcType         = double;
  static constexpr auto ONE = static_cast<FltCalcType>(1.0F);
  [[nodiscard]] auto GetAdjustedPhase(const std::complex<FltCalcType>& fz,
                                      float sqDistFromZero) const noexcept
      -> std::complex<FltCalcType>;
  [[nodiscard]] auto GetModulatedPhase(const std::complex<FltCalcType>& phase,
                                       FltCalcType absSqFz) const noexcept
      -> std::complex<FltCalcType>;
};

inline auto ExpReciprocal::GetZoomInCoefficientsViewport() const noexcept -> Viewport
{
  return m_params.viewport;
}

inline auto ExpReciprocal::GetParams() const noexcept -> const Params&
{
  return m_params;
}

inline void ExpReciprocal::SetParams(const Params& params) noexcept
{
  m_params = params;
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
