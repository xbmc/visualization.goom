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
static const std::vector<vivid::srgb_t> Lisbon_19
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.75294f,   0.79216f,   0.91373f },
  {   0.60784f,   0.68627f,   0.82745f },
  {   0.46667f,   0.58039f,   0.74118f },
  {   0.31765f,   0.46667f,   0.64314f },
  {   0.19608f,   0.36078f,   0.53333f },
  {   0.11765f,   0.26275f,   0.40784f },
  {   0.07843f,   0.18039f,   0.28235f },
  {   0.06667f,   0.11765f,   0.17255f },
  {   0.09020f,   0.09804f,   0.09804f },
  {   0.15294f,   0.14510f,   0.10196f },
  {   0.24314f,   0.22745f,   0.14510f },
  {   0.34118f,   0.31765f,   0.20392f },
  {   0.44314f,   0.41961f,   0.26667f },
  {   0.55294f,   0.52157f,   0.33725f },
  {   0.67059f,   0.63529f,   0.43137f },
  {   0.78824f,   0.76471f,   0.56471f },
  {   0.89412f,   0.88235f,   0.70588f },
  {   1.00000f,   1.00000f,   0.85098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
