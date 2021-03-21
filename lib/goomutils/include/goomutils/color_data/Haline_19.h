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
static const std::vector<vivid::srgb_t> Haline_19
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.18039f,   0.10980f,   0.55686f },
  {   0.14510f,   0.17647f,   0.63922f },
  {   0.07843f,   0.26275f,   0.61176f },
  {   0.04706f,   0.32941f,   0.57647f },
  {   0.07843f,   0.38431f,   0.55686f },
  {   0.12549f,   0.43137f,   0.54510f },
  {   0.16863f,   0.47843f,   0.53725f },
  {   0.20392f,   0.52549f,   0.53333f },
  {   0.23529f,   0.57647f,   0.52941f },
  {   0.26275f,   0.62745f,   0.51765f },
  {   0.29804f,   0.67843f,   0.50196f },
  {   0.35294f,   0.72549f,   0.47059f },
  {   0.42353f,   0.77255f,   0.43137f },
  {   0.52549f,   0.81569f,   0.38431f },
  {   0.65882f,   0.84706f,   0.36078f },
  {   0.79216f,   0.87451f,   0.41176f },
  {   0.89804f,   0.90196f,   0.50196f },
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
