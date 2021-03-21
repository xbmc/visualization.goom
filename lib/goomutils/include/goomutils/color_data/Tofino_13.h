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
static const std::vector<vivid::srgb_t> Tofino_13
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.65098f,   0.69412f,   0.90196f },
  {   0.43137f,   0.53725f,   0.79608f },
  {   0.24314f,   0.36863f,   0.60392f },
  {   0.15294f,   0.23529f,   0.39608f },
  {   0.08627f,   0.12549f,   0.20392f },
  {   0.05098f,   0.08627f,   0.07451f },
  {   0.08235f,   0.17255f,   0.09412f },
  {   0.14118f,   0.30196f,   0.15686f },
  {   0.21569f,   0.45098f,   0.23529f },
  {   0.36078f,   0.61961f,   0.34118f },
  {   0.61569f,   0.77255f,   0.48235f },
  {   0.85882f,   0.90196f,   0.60784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
