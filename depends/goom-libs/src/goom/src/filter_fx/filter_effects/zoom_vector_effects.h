#pragma once

#include "filter_fx/after_effects/zoom_vector_after_effects.h"
#include "filter_fx/filter_settings.h"
#include "filter_fx/normalized_coords.h"
#include "filter_fx/zoom_in_coefficients_effect.h"
#include "point2d.h"
#include "utils/name_value_pairs.h"

#include <functional>

namespace GOOM::UTILS::MATH
{
class IGoomRand;
}

namespace GOOM::FILTER_FX::FILTER_EFFECTS
{

class ZoomVectorEffects
{
public:
  static constexpr auto MIN_ALLOWED_BASE_ZOOM_IN_COEFF = 0.0F;
  static constexpr auto MAX_ALLOWED_BASE_ZOOM_IN_COEFF = 0.5F;
  static constexpr auto RAW_BASE_ZOOM_IN_COEFF_FACTOR  = 0.02F;
  [[nodiscard]] static constexpr auto GetBaseZoomInCoeff(float baseZoomInCoeffFactor,
                                                         float relativeSpeed) noexcept -> float;

  using GetAfterEffectsFunc = std::function<auto(const UTILS::MATH::IGoomRand& goomRand,
                                                 const std::string& resourcesDirectory)
                                                ->AFTER_EFFECTS::AfterEffects>;
  [[nodiscard]] static auto GetStandardAfterEffects(const UTILS::MATH::IGoomRand& goomRand,
                                                    const std::string& resourcesDirectory) noexcept
      -> AFTER_EFFECTS::AfterEffects;

  ZoomVectorEffects(uint32_t screenWidth,
                    const std::string& resourcesDirectory,
                    const UTILS::MATH::IGoomRand& goomRand,
                    const NormalizedCoordsConverter& normalizedCoordsConverter,
                    const GetAfterEffectsFunc& getAfterEffects) noexcept;

  auto SetFilterSettings(const ZoomFilterEffectsSettings& filterEffectsSettings) noexcept -> void;

  [[nodiscard]] auto GetZoomInCoefficients(const NormalizedCoords& coords,
                                           float sqDistFromZero) const noexcept -> Point2dFlt;
  [[nodiscard]] auto GetCleanedCoords(const NormalizedCoords& coords) const noexcept
      -> NormalizedCoords;

  [[nodiscard]] auto GetAfterEffectsVelocity(const NormalizedCoords& coords,
                                             float sqDistFromZero,
                                             const NormalizedCoords& zoomInVelocity) const noexcept
      -> NormalizedCoords;

  [[nodiscard]] auto GetZoomEffectsNameValueParams() const noexcept -> UTILS::NameValuePairs;

private:
  const NormalizedCoordsConverter& m_normalizedCoordsConverter;
  const ZoomFilterEffectsSettings* m_filterEffectsSettings{};
  AFTER_EFFECTS::ZoomVectorAfterEffects m_zoomVectorAfterEffects;
  float m_baseZoomInCoeffFactor = RAW_BASE_ZOOM_IN_COEFF_FACTOR;
  auto SetBaseZoomInCoeffFactor(float multiplier) noexcept -> void;
  auto SetBaseZoomInCoeffs() noexcept -> void;

  [[nodiscard]] auto GetClampedZoomInCoeffs(const Point2dFlt& zoomCoeffs) const noexcept
      -> Point2dFlt;
  [[nodiscard]] auto GetClampedZoomInCoeff(float zoomCoeff) const noexcept -> float;
  [[nodiscard]] static auto GetMinCoordVal(float coordVal, float minNormalizedCoordVal) noexcept
      -> float;

  [[nodiscard]] auto GetZoomInCoeffsNameValueParams() const noexcept -> UTILS::NameValuePairs;
};

inline auto ZoomVectorEffects::GetZoomInCoefficients(const NormalizedCoords& coords,
                                                     const float sqDistFromZero) const noexcept
    -> Point2dFlt
{
  const auto zoomCoeffs = m_filterEffectsSettings->zoomInCoefficientsEffect->GetZoomInCoefficients(
      coords, sqDistFromZero);
  // Amulet 2
  // vx = X * tan(dist);
  // vy = Y * tan(dist);
  return GetClampedZoomInCoeffs(zoomCoeffs);
}

inline auto ZoomVectorEffects::SetBaseZoomInCoeffFactor(const float multiplier) noexcept -> void
{
  Expects(multiplier > 0.0F);

  m_baseZoomInCoeffFactor = multiplier * RAW_BASE_ZOOM_IN_COEFF_FACTOR;

  Ensures(GetBaseZoomInCoeff(m_baseZoomInCoeffFactor,
                             m_filterEffectsSettings->vitesse.GetRelativeSpeed()) <=
          MAX_ALLOWED_BASE_ZOOM_IN_COEFF);

  SetBaseZoomInCoeffs();
}

inline auto ZoomVectorEffects::SetBaseZoomInCoeffs() noexcept -> void
{
  // TODO(glk) Does GetRelativeSpeed change in between this setter use?
  const auto baseZoomCoeff = GetBaseZoomInCoeff(
      m_baseZoomInCoeffFactor, m_filterEffectsSettings->vitesse.GetRelativeSpeed());

  Ensures(MIN_ALLOWED_BASE_ZOOM_IN_COEFF <= baseZoomCoeff);
  Ensures(baseZoomCoeff <= MAX_ALLOWED_BASE_ZOOM_IN_COEFF);

  m_filterEffectsSettings->zoomInCoefficientsEffect->SetBaseZoomInCoeffs(
      {baseZoomCoeff, baseZoomCoeff});
}

constexpr auto ZoomVectorEffects::GetBaseZoomInCoeff(const float baseZoomInCoeffFactor,
                                                     const float relativeSpeed) noexcept -> float
{
  return baseZoomInCoeffFactor * (1.0F + relativeSpeed);
}

static_assert(
    ZoomVectorEffects::MIN_ALLOWED_BASE_ZOOM_IN_COEFF <=
    ZoomVectorEffects::GetBaseZoomInCoeff(ZoomVectorEffects::RAW_BASE_ZOOM_IN_COEFF_FACTOR, -1.0F));
static_assert(
    ZoomVectorEffects::MAX_ALLOWED_BASE_ZOOM_IN_COEFF >=
    ZoomVectorEffects::GetBaseZoomInCoeff(ZoomVectorEffects::RAW_BASE_ZOOM_IN_COEFF_FACTOR, +1.0F));

inline auto ZoomVectorEffects::GetClampedZoomInCoeffs(const Point2dFlt& zoomCoeffs) const noexcept
    -> Point2dFlt
{
  return {GetClampedZoomInCoeff(zoomCoeffs.x), GetClampedZoomInCoeff(zoomCoeffs.y)};
}

inline auto ZoomVectorEffects::GetClampedZoomInCoeff(const float zoomCoeff) const noexcept -> float
{
  if (static constexpr auto MIN_ZOOM_COEFF = -4.01F; zoomCoeff < MIN_ZOOM_COEFF)
  {
    return MIN_ZOOM_COEFF;
  }
  if (zoomCoeff > m_filterEffectsSettings->maxZoomInCoeff)
  {
    return m_filterEffectsSettings->maxZoomInCoeff;
  }
  return zoomCoeff;
}

inline auto ZoomVectorEffects::GetAfterEffectsVelocity(
    const NormalizedCoords& coords,
    const float sqDistFromZero,
    const NormalizedCoords& zoomInVelocity) const noexcept -> NormalizedCoords
{
  return m_zoomVectorAfterEffects.GetAfterEffectsVelocity(coords, sqDistFromZero, zoomInVelocity);
}

} // namespace GOOM::FILTER_FX::FILTER_EFFECTS
