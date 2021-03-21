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
static const std::vector<vivid::srgb_t> Amp_16
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.91373f,   0.85098f,   0.83137f },
  {   0.88627f,   0.77255f,   0.73725f },
  {   0.86275f,   0.69412f,   0.63922f },
  {   0.83922f,   0.61961f,   0.54510f },
  {   0.81569f,   0.54510f,   0.45098f },
  {   0.79216f,   0.46667f,   0.35686f },
  {   0.76471f,   0.38824f,   0.27451f },
  {   0.73725f,   0.30588f,   0.19608f },
  {   0.70196f,   0.21961f,   0.14902f },
  {   0.65098f,   0.13333f,   0.14510f },
  {   0.58039f,   0.07451f,   0.15686f },
  {   0.49804f,   0.05490f,   0.16078f },
  {   0.40784f,   0.05882f,   0.14510f },
  {   0.32157f,   0.05098f,   0.10980f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
