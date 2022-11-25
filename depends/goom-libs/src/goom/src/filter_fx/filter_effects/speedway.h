#pragma once

#include "filter_fx/common_types.h"
#include "filter_fx/normalized_coords.h"
#include "filter_fx/zoom_in_coefficients_effect.h"
#include "goom_config.h"
#include "point2d.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

class Speedway : public IZoomInCoefficientsEffect
{
public:
  enum class Modes
  {
    MODE0,
    MODE1,
    MODE2,
  };
  Speedway(Modes mode, const UTILS::MATH::IGoomRand& goomRand) noexcept;

  auto SetRandomParams() noexcept -> void override;

  [[nodiscard]] auto GetZoomInCoefficients(const NormalizedCoords& coords,
                                           float sqDistFromZero) const noexcept
      -> Point2dFlt override;

  [[nodiscard]] auto GetZoomInCoefficientsEffectNameValueParams() const noexcept
      -> UTILS::NameValuePairs override;

  struct Params
  {
    Amplitude amplitude;
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
  auto SetMode2RandomParams() noexcept -> void;
  [[nodiscard]] auto GetMode0ZoomInCoefficients(const NormalizedCoords& coords,
                                                float sqDistFromZero) const noexcept -> Point2dFlt;
  [[nodiscard]] auto GetMode1ZoomInCoefficients(const NormalizedCoords& coords,
                                                float sqDistFromZero) const noexcept -> Point2dFlt;
  [[nodiscard]] auto GetMode2ZoomInCoefficients(const NormalizedCoords& coords,
                                                float sqDistFromZero) const noexcept -> Point2dFlt;
};

inline auto Speedway::GetZoomInCoefficients(const NormalizedCoords& coords,
                                            const float sqDistFromZero) const noexcept -> Point2dFlt
{
  switch (m_mode)
  {
    case Modes::MODE0:
      return GetMode0ZoomInCoefficients(coords, sqDistFromZero);
    case Modes::MODE1:
      return GetMode1ZoomInCoefficients(coords, sqDistFromZero);
    case Modes::MODE2:
      return GetMode2ZoomInCoefficients(coords, sqDistFromZero);
    default:
      FailFast();
      return {};
  }
}

inline auto Speedway::GetMode0ZoomInCoefficients(const NormalizedCoords& coords,
                                                 const float sqDistFromZero) const noexcept
    -> Point2dFlt
{
  static constexpr auto SQ_DIST_FACTOR = 0.01F;

  auto xAdd = SQ_DIST_FACTOR * sqDistFromZero;
  if (static constexpr auto PROB_FLIP_X_ADD = 0.5F; m_goomRand.ProbabilityOf(PROB_FLIP_X_ADD))
  {
    xAdd = -xAdd;
  }

  const auto xZoomInCoeff =
      GetBaseZoomInCoeffs().x * (m_params.amplitude.x * (coords.GetY() + xAdd));
  const auto yZoomInCoeff = m_params.amplitude.y * xZoomInCoeff;

  return {xZoomInCoeff, yZoomInCoeff};
}

inline auto Speedway::GetMode1ZoomInCoefficients(const NormalizedCoords& coords,
                                                 const float sqDistFromZero) const noexcept
    -> Point2dFlt
{
  auto xAdd = -1.0F;
  if (static constexpr auto PROB_RANDOM_X_ADD = 0.5F; m_goomRand.ProbabilityOf(PROB_RANDOM_X_ADD))
  {
    static constexpr auto MIN_NEGATIVE_X_ADD  = -1.9F;
    static constexpr auto MAX_NEGATIVE_X_ADD  = -0.5F;
    static constexpr auto MIN_POSITIVE_X_ADD  = +0.5F;
    static constexpr auto MAX_POSITIVE_X_ADD  = +1.9F;
    static constexpr auto PROB_NEGATIVE_X_ADD = 0.5F;

    xAdd = m_goomRand.ProbabilityOf(PROB_NEGATIVE_X_ADD)
               ? m_goomRand.GetRandInRange(MIN_NEGATIVE_X_ADD, MAX_NEGATIVE_X_ADD)
               : m_goomRand.GetRandInRange(MIN_POSITIVE_X_ADD, MAX_POSITIVE_X_ADD);
  }
  else if (static constexpr auto PROB_FLIP_X_ADD = 0.5F; m_goomRand.ProbabilityOf(PROB_FLIP_X_ADD))
  {
    xAdd = -xAdd;
  }

  static constexpr auto X_WARP_MULTIPLIER    = 0.1F;
  static constexpr auto AMPLITUDE_MULTIPLIER = 0.25F;

  const auto xDiff     = coords.GetX() - xAdd;
  const auto sign      = xDiff < 0.0F ? -1.0F : +1.0F;
  const auto xWarp     = X_WARP_MULTIPLIER * (xAdd + ((sign * UTILS::MATH::Sq(xDiff)) / xAdd));
  const auto amplitude = AMPLITUDE_MULTIPLIER * (1.0F - sqDistFromZero);

  const auto xZoomInCoeff = amplitude * GetBaseZoomInCoeffs().x * (m_params.amplitude.x * xWarp);
  const auto yZoomInCoeff = amplitude * m_params.amplitude.y * xZoomInCoeff;

  return {xZoomInCoeff, yZoomInCoeff};
}

inline auto Speedway::GetMode2ZoomInCoefficients(const NormalizedCoords& coords,
                                                 const float sqDistFromZero) const noexcept
    -> Point2dFlt
{
  static constexpr auto SQ_DIST_FACTOR = 0.01F;

  auto xAdd = SQ_DIST_FACTOR * sqDistFromZero;
  if (static constexpr auto PROB_FLIP_X_ADD = 0.5F; m_goomRand.ProbabilityOf(PROB_FLIP_X_ADD))
  {
    xAdd = -xAdd;
  }

  const auto xZoomInCoeff =
      GetBaseZoomInCoeffs().x * (m_params.amplitude.x * (coords.GetY() + xAdd));
  const auto yZoomInCoeff = std::tan(0.01F * sqDistFromZero) * m_params.amplitude.y * xZoomInCoeff;

  return {xZoomInCoeff, yZoomInCoeff};
}

inline auto Speedway::GetParams() const noexcept -> const Params&
{
  return m_params;
}

inline auto Speedway::SetParams(const Params& params) noexcept -> void
{
  m_params = params;
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
