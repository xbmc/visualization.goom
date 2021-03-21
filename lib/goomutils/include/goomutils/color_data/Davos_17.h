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
static const std::vector<vivid::srgb_t> Davos_17
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.03137f,   0.10980f,   0.38039f },
  {   0.07843f,   0.19608f,   0.46667f },
  {   0.12941f,   0.27843f,   0.53725f },
  {   0.18431f,   0.35294f,   0.58824f },
  {   0.24314f,   0.41961f,   0.61176f },
  {   0.30588f,   0.47451f,   0.61569f },
  {   0.36471f,   0.51765f,   0.60000f },
  {   0.42353f,   0.55686f,   0.57647f },
  {   0.47843f,   0.59216f,   0.55294f },
  {   0.54510f,   0.63922f,   0.53333f },
  {   0.62745f,   0.69804f,   0.53725f },
  {   0.73333f,   0.78039f,   0.58039f },
  {   0.85098f,   0.87451f,   0.67843f },
  {   0.93725f,   0.94118f,   0.79608f },
  {   0.98039f,   0.97647f,   0.90196f },
  {   0.99608f,   0.99608f,   0.99608f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
