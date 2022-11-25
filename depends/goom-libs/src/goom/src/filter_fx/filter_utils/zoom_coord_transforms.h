#pragma once

#include "../normalized_coords.h"
#include "point2d.h"
#include "utils/math/misc.h"
#include "zoom_filter_coefficients.h"

#include <cstdint>

namespace GOOM::FILTER_FX::FILTER_UTILS
{

class ZoomCoordTransforms
{
public:
  explicit ZoomCoordTransforms(const Dimensions& screenDimensions) noexcept;

  [[nodiscard]] static auto TranCoordToZoomCoeffIndexes(const Point2dInt& tranPoint) noexcept
      -> std::pair<uint32_t, uint32_t>;

  [[nodiscard]] auto NormalizedToTranPoint(const NormalizedCoords& normalizedPoint) const noexcept
      -> Point2dInt;

  [[nodiscard]] static auto TranToScreenPoint(const Point2dInt& tranPoint) noexcept -> Point2dInt;
  [[nodiscard]] static auto ScreenToTranPoint(const Point2dInt& screenPoint) noexcept -> Point2dInt;

private:
  const NormalizedCoordsConverter m_normalizedCoordsConverter;
  [[nodiscard]] static auto ScreenToTranCoord(float screenCoord) noexcept -> uint32_t;
};

inline ZoomCoordTransforms::ZoomCoordTransforms(const Dimensions& screenDimensions) noexcept
  : m_normalizedCoordsConverter{
        {screenDimensions.GetWidth() << ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS_EXP,
         screenDimensions.GetWidth() << ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS_EXP},
        1.0F / static_cast<float>(ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS)
}
{
}

inline auto ZoomCoordTransforms::TranToScreenPoint(const Point2dInt& tranPoint) noexcept
    -> Point2dInt
{
  // Note: Truncation here but seems OK. Trying to round adds about 2ms.
  return {tranPoint.x >> ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS_EXP,
          tranPoint.y >> ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS_EXP};
}

inline auto ZoomCoordTransforms::ScreenToTranPoint(const Point2dInt& screenPoint) noexcept
    -> Point2dInt
{
  return {screenPoint.x << ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS_EXP,
          screenPoint.y << ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS_EXP};
}

inline auto ZoomCoordTransforms::ScreenToTranCoord(const float screenCoord) noexcept -> uint32_t
{
  // IMPORTANT: Without 'lround' a faint cross artifact appears in the centre of the screen.
  return static_cast<uint32_t>(
      std::lround(screenCoord * static_cast<float>(ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS)));
}

inline auto ZoomCoordTransforms::TranCoordToZoomCoeffIndexes(const Point2dInt& tranPoint) noexcept
    -> std::pair<uint32_t, uint32_t>
{
  return {static_cast<uint32_t>(tranPoint.x) & ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS_MOD_MASK,
          static_cast<uint32_t>(tranPoint.y) & ZOOM_FILTER_COEFFS::DIM_FILTER_COEFFS_MOD_MASK};
}

inline auto ZoomCoordTransforms::NormalizedToTranPoint(
    const NormalizedCoords& normalizedPoint) const noexcept -> Point2dInt
{
  return m_normalizedCoordsConverter.NormalizedToOtherCoordsFlt(normalizedPoint).ToInt();
}

} // namespace GOOM::FILTER_FX::FILTER_UTILS
