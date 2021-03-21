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
static const std::vector<vivid::srgb_t> LaJolla_17
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.99216f,   0.96078f,   0.68627f },
  {   0.98431f,   0.91373f,   0.57255f },
  {   0.96863f,   0.84706f,   0.45882f },
  {   0.94902f,   0.76471f,   0.37647f },
  {   0.92941f,   0.68235f,   0.33725f },
  {   0.91373f,   0.60784f,   0.32549f },
  {   0.89804f,   0.53333f,   0.31765f },
  {   0.87059f,   0.45490f,   0.30980f },
  {   0.81569f,   0.38039f,   0.29804f },
  {   0.72157f,   0.30980f,   0.27843f },
  {   0.61176f,   0.26667f,   0.24706f },
  {   0.49804f,   0.23137f,   0.20392f },
  {   0.38824f,   0.20000f,   0.15686f },
  {   0.28627f,   0.16471f,   0.10588f },
  {   0.18824f,   0.13333f,   0.06275f },
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
