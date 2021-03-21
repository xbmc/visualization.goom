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
static const std::vector<vivid::srgb_t> Buda_19
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.70196f,   0.10196f,   0.65490f },
  {   0.70196f,   0.16863f,   0.61961f },
  {   0.70980f,   0.22353f,   0.59608f },
  {   0.72549f,   0.28235f,   0.57255f },
  {   0.74510f,   0.33333f,   0.55686f },
  {   0.76078f,   0.38039f,   0.54118f },
  {   0.77647f,   0.42745f,   0.52549f },
  {   0.79216f,   0.47451f,   0.50980f },
  {   0.80392f,   0.52157f,   0.49412f },
  {   0.81961f,   0.56863f,   0.48235f },
  {   0.83137f,   0.61961f,   0.47059f },
  {   0.84314f,   0.66667f,   0.45882f },
  {   0.85490f,   0.71373f,   0.44706f },
  {   0.86667f,   0.76471f,   0.43529f },
  {   0.87843f,   0.81569f,   0.41961f },
  {   0.89804f,   0.87451f,   0.40784f },
  {   0.93725f,   0.93333f,   0.40000f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
