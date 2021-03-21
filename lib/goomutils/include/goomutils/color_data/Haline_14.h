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
static const std::vector<vivid::srgb_t> Haline_14
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.17647f,   0.12549f,   0.61176f },
  {   0.09020f,   0.24706f,   0.61961f },
  {   0.05098f,   0.33725f,   0.57255f },
  {   0.10196f,   0.40784f,   0.54902f },
  {   0.16471f,   0.47451f,   0.53725f },
  {   0.21569f,   0.54118f,   0.53333f },
  {   0.25490f,   0.60784f,   0.52549f },
  {   0.30196f,   0.68235f,   0.49804f },
  {   0.38431f,   0.74902f,   0.45098f },
  {   0.50980f,   0.80784f,   0.38824f },
  {   0.69412f,   0.85098f,   0.36471f },
  {   0.85490f,   0.89020f,   0.45882f },
  {   0.99216f,   0.93725f,   0.60392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
