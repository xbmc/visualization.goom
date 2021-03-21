#pragma once

#include "vivid/types.h"
#include <vector>

#if __cplusplus > 201402L
namespace GOOM::UTILS::COLOR_DATA
{
#else
namespace GOOM
{
namespace UTILS
{
namespace COLOR_DATA
{
#endif

// clang-format off
static const std::vector<vivid::srgb_t> LaJolla_9
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.98431f,   0.91373f,   0.57255f },
  {   0.94902f,   0.76471f,   0.37647f },
  {   0.91373f,   0.60784f,   0.32549f },
  {   0.87059f,   0.45490f,   0.30980f },
  {   0.72157f,   0.30980f,   0.27843f },
  {   0.49804f,   0.23137f,   0.20392f },
  {   0.28627f,   0.16471f,   0.10588f },
  {   0.10196f,   0.10196f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
