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
static const std::vector<vivid::srgb_t> Speed_9
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.91373f,   0.84706f,   0.53725f },
  {   0.78824f,   0.72941f,   0.27059f },
  {   0.59608f,   0.64706f,   0.07059f },
  {   0.37255f,   0.57255f,   0.04706f },
  {   0.15686f,   0.48627f,   0.13725f },
  {   0.04314f,   0.37647f,   0.17647f },
  {   0.09020f,   0.25490f,   0.15294f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
