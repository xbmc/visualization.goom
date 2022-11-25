#pragma once

#include "filter_fx/normalized_coords.h"
#include "point2d.h"
#include "utils/name_value_pairs.h"

namespace GOOM::FILTER_FX
{

class IZoomInCoefficientsEffect
{
public:
  IZoomInCoefficientsEffect() noexcept                                           = default;
  IZoomInCoefficientsEffect(const IZoomInCoefficientsEffect&) noexcept           = default;
  IZoomInCoefficientsEffect(IZoomInCoefficientsEffect&&) noexcept                = default;
  virtual ~IZoomInCoefficientsEffect() noexcept                                  = default;
  auto operator=(const IZoomInCoefficientsEffect&) -> IZoomInCoefficientsEffect& = default;
  auto operator=(IZoomInCoefficientsEffect&&) -> IZoomInCoefficientsEffect&      = default;

  virtual auto SetRandomParams() noexcept -> void = 0;
  [[nodiscard]] virtual auto GetZoomInCoefficientsViewport() const noexcept -> Viewport;

  auto SetBaseZoomInCoeffs(const Point2dFlt& baseZoomInCoeffs) noexcept -> void;

  [[nodiscard]] virtual auto GetZoomInCoefficients(const NormalizedCoords& coords,
                                                   float sqDistFromZero) const noexcept
      -> Point2dFlt = 0;

  [[nodiscard]] virtual auto GetZoomInCoefficientsEffectNameValueParams() const noexcept
      -> GOOM::UTILS::NameValuePairs = 0;

protected:
  static constexpr auto* PARAM_GROUP = "Zoom Coeffs";
  [[nodiscard]] auto GetBaseZoomInCoeffs() const noexcept -> const Point2dFlt&;

private:
  Point2dFlt m_baseZoomInCoeffs{};
};

inline auto IZoomInCoefficientsEffect::GetZoomInCoefficientsViewport() const noexcept -> Viewport
{
  return Viewport{};
}

inline auto IZoomInCoefficientsEffect::GetBaseZoomInCoeffs() const noexcept -> const Point2dFlt&
{
  return m_baseZoomInCoeffs;
}

inline auto IZoomInCoefficientsEffect::SetBaseZoomInCoeffs(
    const Point2dFlt& baseZoomInCoeffs) noexcept -> void
{
  m_baseZoomInCoeffs = baseZoomInCoeffs;
}

} // namespace GOOM::FILTER_FX
