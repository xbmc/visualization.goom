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
static const std::vector<vivid::srgb_t> Haline_10
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.14510f,   0.17647f,   0.63922f },
  {   0.04706f,   0.32941f,   0.57647f },
  {   0.12549f,   0.43137f,   0.54510f },
  {   0.20392f,   0.52549f,   0.53333f },
  {   0.26275f,   0.62745f,   0.51765f },
  {   0.35294f,   0.72549f,   0.47059f },
  {   0.52549f,   0.81569f,   0.38431f },
  {   0.79216f,   0.87451f,   0.41176f },
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
