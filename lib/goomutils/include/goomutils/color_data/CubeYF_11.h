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
static const std::vector<vivid::srgb_t> CubeYF_11
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.52157f,   0.16863f,   0.80000f },
  {   0.45098f,   0.34118f,   0.97255f },
  {   0.38431f,   0.48627f,   0.97255f },
  {   0.29804f,   0.61961f,   0.85098f },
  {   0.22353f,   0.72941f,   0.69412f },
  {   0.27843f,   0.80392f,   0.52157f },
  {   0.34510f,   0.87059f,   0.34118f },
  {   0.46275f,   0.91373f,   0.30196f },
  {   0.67843f,   0.92549f,   0.33725f },
  {   0.81961f,   0.92157f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
