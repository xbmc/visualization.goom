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
static const std::vector<vivid::srgb_t> Bilbao_10
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.86275f,   0.85882f,   0.85098f },
  {   0.77255f,   0.75294f,   0.68627f },
  {   0.72549f,   0.68627f,   0.54510f },
  {   0.68235f,   0.58039f,   0.42745f },
  {   0.65098f,   0.47843f,   0.37647f },
  {   0.61961f,   0.38039f,   0.33333f },
  {   0.55294f,   0.26275f,   0.25490f },
  {   0.43137f,   0.13333f,   0.13333f },
  {   0.30196f,   0.00000f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
