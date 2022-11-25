#include "image_displacement.h"

#include "filter_fx/normalized_coords.h"
#include "goom_graphic.h"
#include "point2d.h"
#include "utils/graphics/image_bitmaps.h"

#include <cmath>
#include <memory>

namespace GOOM::FILTER_FX::FILTER_UTILS
{

using UTILS::GRAPHICS::ImageBitmap;
using UTILS::MATH::IGoomRand;

ImageDisplacement::ImageDisplacement(const std::string& imageFilename,
                                     [[maybe_unused]] const IGoomRand& goomRand)
  : m_imageBuffer(std::make_unique<ImageBitmap>(imageFilename)), m_imageFilename{imageFilename}
{
}

ImageDisplacement::~ImageDisplacement() noexcept = default;

auto ImageDisplacement::GetDisplacementVector(const NormalizedCoords& normalizedCoords) const
    -> Point2dFlt
{
  const auto imagePoint = NormalizedCoordsToImagePoint(normalizedCoords);

  if ((imagePoint.x < 0) || (imagePoint.x > m_xMax))
  {
    return {0.0F, 0.0F};
  }
  if ((imagePoint.y < 0) || (imagePoint.y > m_yMax))
  {
    return {0.0F, 0.0F};
  }

  const auto color =
      (*m_imageBuffer)(static_cast<size_t>(imagePoint.x), static_cast<size_t>(imagePoint.y));

  return ColorToNormalizedDisplacement(color);
}

inline auto ImageDisplacement::NormalizedCoordsToImagePoint(
    const NormalizedCoords& normalizedCoords) const -> Point2dInt
{
  const auto normalizedZoom = m_zoomFactor * normalizedCoords;
  return m_normalizedCoordsConverter.NormalizedToOtherCoordsFlt(normalizedZoom).ToInt();
}

inline auto ImageDisplacement::ColorToNormalizedDisplacement(const Pixel& color) const -> Point2dFlt
{
  const auto normalizedDisplacementX =
      NormalizedCoords::MAX_COORD * m_amplitude * (color.RFlt() - m_xColorCutoff);
  const auto normalizedDisplacementY =
      NormalizedCoords::MAX_COORD * m_amplitude * (color.GFlt() - m_yColorCutoff);
  //const auto normalizedDisplacementY =
  //         (ProbabilityOfMInN(1, 2) ? color.GFlt() : color.BFlt()) - 0.5F;

  return {normalizedDisplacementX, normalizedDisplacementY};
}

} // namespace GOOM::FILTER_FX::FILTER_UTILS
