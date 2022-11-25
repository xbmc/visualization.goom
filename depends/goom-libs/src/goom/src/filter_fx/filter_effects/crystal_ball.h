#pragma once

#include "filter_fx/common_types.h"
#include "filter_fx/normalized_coords.h"
#include "filter_fx/zoom_in_coefficients_effect.h"
#include "point2d.h"
#include "utils/math/goom_rand_base.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

class CrystalBall : public IZoomInCoefficientsEffect
{
public:
  enum class Modes
  {
    MODE0,
    MODE1
  };
  explicit CrystalBall(Modes mode, const UTILS::MATH::IGoomRand& goomRand) noexcept;

  auto SetRandomParams() noexcept -> void override;

  [[nodiscard]] auto GetZoomInCoefficients(const NormalizedCoords& coords,
                                           float sqDistFromZero) const noexcept
      -> Point2dFlt override;

  [[nodiscard]] auto GetZoomInCoefficientsEffectNameValueParams() const noexcept
      -> UTILS::NameValuePairs override;

  struct Params
  {
    Amplitude amplitude;
    SqDistMult sqDistMult;
    SqDistOffset sqDistOffset;
  };
  [[nodiscard]] auto GetParams() const noexcept -> const Params&;

protected:
  auto SetParams(const Params& params) noexcept -> void;

private:
  const Modes m_mode;
  const UTILS::MATH::IGoomRand& m_goomRand;
  Params m_params;
  auto SetMode0RandomParams() noexcept -> void;
  auto SetMode1RandomParams() noexcept -> void;
  auto SetRandomParams(const AmplitudeRange& amplitudeRange,
                       const SqDistMultRange& sqDistMultRange,
                       const SqDistOffsetRange& sqDistOffsetRange) noexcept -> void;
  [[nodiscard]] static auto GetZoomInCoefficient(float baseZoomInCoeff,
                                                 float sqDistFromZero,
                                                 float amplitude,
                                                 float sqDistMult,
                                                 float sqDistOffset) noexcept -> float;
};

inline auto CrystalBall::GetZoomInCoefficients([[maybe_unused]] const NormalizedCoords& coords,
                                               const float sqDistFromZero) const noexcept
    -> Point2dFlt
{
  return {GetZoomInCoefficient(GetBaseZoomInCoeffs().x,
                               sqDistFromZero,
                               m_params.amplitude.x,
                               m_params.sqDistMult.x,
                               m_params.sqDistOffset.x),
          GetZoomInCoefficient(GetBaseZoomInCoeffs().y,
                               sqDistFromZero,
                               m_params.amplitude.y,
                               m_params.sqDistMult.y,
                               m_params.sqDistOffset.y)};
}

inline auto CrystalBall::GetZoomInCoefficient(const float baseZoomInCoeff,
                                              const float sqDistFromZero,
                                              const float amplitude,
                                              const float sqDistMult,
                                              const float sqDistOffset) noexcept -> float
{
  return baseZoomInCoeff - (amplitude * ((sqDistMult * sqDistFromZero) - sqDistOffset));
}

inline auto CrystalBall::GetParams() const noexcept -> const Params&
{
  return m_params;
}

inline auto CrystalBall::SetParams(const Params& params) noexcept -> void
{
  m_params = params;
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
