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
static const std::vector<vivid::srgb_t> Oslo_18
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.03529f,   0.06667f,   0.09804f },
  {   0.05490f,   0.10980f,   0.17255f },
  {   0.06275f,   0.15686f,   0.25098f },
  {   0.07843f,   0.20784f,   0.33333f },
  {   0.10196f,   0.26275f,   0.42353f },
  {   0.13333f,   0.31765f,   0.51373f },
  {   0.18431f,   0.37647f,   0.60784f },
  {   0.26275f,   0.44314f,   0.69804f },
  {   0.35686f,   0.51373f,   0.76471f },
  {   0.43922f,   0.56863f,   0.78824f },
  {   0.51373f,   0.61569f,   0.79216f },
  {   0.58039f,   0.65882f,   0.78824f },
  {   0.65490f,   0.70588f,   0.79216f },
  {   0.72941f,   0.76078f,   0.80784f },
  {   0.81961f,   0.82745f,   0.85098f },
  {   0.90980f,   0.91373f,   0.91765f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
