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
static const std::vector<vivid::srgb_t> Amp_18
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.91373f,   0.85882f,   0.84314f },
  {   0.89020f,   0.78824f,   0.76078f },
  {   0.87059f,   0.72157f,   0.67451f },
  {   0.84706f,   0.65490f,   0.58824f },
  {   0.82745f,   0.58824f,   0.50588f },
  {   0.80784f,   0.52157f,   0.42353f },
  {   0.78824f,   0.45490f,   0.34118f },
  {   0.76471f,   0.38431f,   0.26667f },
  {   0.74118f,   0.30980f,   0.20000f },
  {   0.70980f,   0.23529f,   0.15294f },
  {   0.66667f,   0.15686f,   0.14118f },
  {   0.61176f,   0.09412f,   0.15294f },
  {   0.54510f,   0.05882f,   0.16078f },
  {   0.46667f,   0.05490f,   0.15686f },
  {   0.38824f,   0.05490f,   0.13725f },
  {   0.30980f,   0.05098f,   0.10588f },
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
