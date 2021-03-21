#include "filter_normalized_coords.h"

#undef NDEBUG
#include <cassert>
#include <cstdint>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace FILTERS
{
#else
namespace GOOM::FILTERS
{
#endif

// clang linking trouble with C++14 - should be able to use static constexpr
const float NormalizedCoords::MAX_NORMALIZED_COORD = 2.0;
const float NormalizedCoords::MIN_NORMALIZED_COORD = -MAX_NORMALIZED_COORD;
float NormalizedCoords::s_ratioScreenToNormalizedCoord = 1.0;
float NormalizedCoords::s_ratioNormalizedToScreenCoord = 1.0;
float NormalizedCoords::s_minNormalizedCoordVal = 0.0;

void NormalizedCoords::SetScreenDimensions(const uint32_t width,
                                           [[maybe_unused]] const uint32_t height,
                                           const float minScreenCoordVal)
{
  assert(width > 1);
  assert(height > 1);
  s_ratioScreenToNormalizedCoord = MAX_NORMALIZED_COORD / static_cast<float>(width - 1);
  s_ratioNormalizedToScreenCoord = 1.0F / s_ratioScreenToNormalizedCoord;
  s_minNormalizedCoordVal = minScreenCoordVal * s_ratioScreenToNormalizedCoord;
}

#if __cplusplus <= 201402L
} // namespace FILTERS
} // namespace GOOM
#else
} // namespace GOOM::FILTERS
#endif
