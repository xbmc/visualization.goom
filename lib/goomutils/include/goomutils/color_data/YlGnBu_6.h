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
static const std::vector<vivid::srgb_t> YlGnBu_6
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.78039f,   0.91373f,   0.70588f },
  {   0.49804f,   0.80392f,   0.73333f },
  {   0.25490f,   0.71373f,   0.76863f },
  {   0.17255f,   0.49804f,   0.72157f },
  {   0.14510f,   0.20392f,   0.58039f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
