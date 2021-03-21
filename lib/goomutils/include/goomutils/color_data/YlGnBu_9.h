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
static const std::vector<vivid::srgb_t> YlGnBu_9
{
  {   1.00000f,   1.00000f,   0.85098f },
  {   0.92941f,   0.97255f,   0.69412f },
  {   0.78039f,   0.91373f,   0.70588f },
  {   0.49804f,   0.80392f,   0.73333f },
  {   0.25490f,   0.71373f,   0.76863f },
  {   0.11373f,   0.56863f,   0.75294f },
  {   0.13333f,   0.36863f,   0.65882f },
  {   0.14510f,   0.20392f,   0.58039f },
  {   0.03137f,   0.11373f,   0.34510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
