#include "image_displacement.h"

#include "filter_normalized_coords.h"
#include "goomutils/goomrand.h"
#include "goomutils/graphics/image_bitmaps.h"
#include "goomutils/mathutils.h"

#include <cmath>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace FILTERS
{
#else
namespace GOOM::FILTERS
{
#endif

using UTILS::GetRandInRange;
using UTILS::ImageBitmap;

ImageDisplacement::ImageDisplacement(const std::string& imageFilename)
  : m_imageBuffer(std::make_unique<ImageBitmap>(imageFilename)),
    m_imageFilename{imageFilename},
    m_xMax{static_cast<int32_t>(m_imageBuffer->GetWidth() - 1)},
    m_yMax{static_cast<int32_t>(m_imageBuffer->GetHeight() - 1)},
    m_ratioNormalizedXCoordToImageCoord{
        static_cast<float>(m_xMax) /
        (NormalizedCoords::MAX_NORMALIZED_COORD - NormalizedCoords::MIN_NORMALIZED_COORD)},
    m_ratioNormalizedYCoordToImageCoord{
        static_cast<float>(m_yMax) /
        (NormalizedCoords::MAX_NORMALIZED_COORD - NormalizedCoords::MIN_NORMALIZED_COORD)}
{
}

ImageDisplacement::~ImageDisplacement() noexcept = default;

auto ImageDisplacement::GetDisplacementVector(const V2dFlt& normalizedPoint) const -> V2dFlt
{
  const V2dInt imagePoint = NormalizedToImagePoint(normalizedPoint);
  const Pixel color =
      (*m_imageBuffer)(static_cast<size_t>(imagePoint.x), static_cast<size_t>(imagePoint.y));

  const float x = color.RFlt() - m_xColorCutoff;
  const float y = color.GFlt() - m_yColorCutoff;
  //const float y = (ProbabilityOfMInN(1, 2) ? color.GFlt() : color.BFlt()) - 0.5F;

  return {x, y};
}

inline auto ImageDisplacement::NormalizedToImagePoint(const V2dFlt& normalizedPoint) const -> V2dInt
{
  const float xZoom =
      std::min(NormalizedCoords::MAX_NORMALIZED_COORD, m_zoomFactor * normalizedPoint.x);
  const float yZoom =
      std::min(NormalizedCoords::MAX_NORMALIZED_COORD, m_zoomFactor * normalizedPoint.y);

  const auto x = static_cast<int32_t>(std::lround(
      m_ratioNormalizedXCoordToImageCoord * (xZoom - NormalizedCoords::MIN_NORMALIZED_COORD)));
  const auto y = static_cast<int32_t>(std::lround(
      m_ratioNormalizedYCoordToImageCoord * (yZoom - NormalizedCoords::MIN_NORMALIZED_COORD)));

  constexpr int32_t FUZZ = 3;
  return {stdnew::clamp(GetRandInRange(x - FUZZ, x + FUZZ), 0, m_xMax),
          stdnew::clamp(GetRandInRange(y - FUZZ, y + FUZZ), 0, m_yMax)};
}

#if __cplusplus <= 201402L
} // namespace FILTERS
} // namespace GOOM
#else
} // namespace GOOM::FILTERS
#endif
