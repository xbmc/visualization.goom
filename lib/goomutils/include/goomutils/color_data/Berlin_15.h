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
static const std::vector<vivid::srgb_t> Berlin_15
{
  {   0.61961f,   0.69020f,   1.00000f },
  {   0.45490f,   0.66667f,   0.92157f },
  {   0.28235f,   0.60392f,   0.79216f },
  {   0.18431f,   0.47059f,   0.61176f },
  {   0.13333f,   0.34118f,   0.44314f },
  {   0.08627f,   0.21961f,   0.28627f },
  {   0.06275f,   0.11373f,   0.14510f },
  {   0.09804f,   0.04706f,   0.03529f },
  {   0.17647f,   0.05490f,   0.00000f },
  {   0.27843f,   0.07843f,   0.00392f },
  {   0.40784f,   0.14118f,   0.05882f },
  {   0.55686f,   0.25882f,   0.18039f },
  {   0.70588f,   0.40000f,   0.34510f },
  {   0.85098f,   0.53725f,   0.50980f },
  {   1.00000f,   0.67843f,   0.67843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
