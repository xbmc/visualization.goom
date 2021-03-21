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
static const std::vector<vivid::srgb_t> Davos_9
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.07843f,   0.19608f,   0.46667f },
  {   0.18431f,   0.35294f,   0.58824f },
  {   0.30588f,   0.47451f,   0.61569f },
  {   0.42353f,   0.55686f,   0.57647f },
  {   0.54510f,   0.63922f,   0.53333f },
  {   0.73333f,   0.78039f,   0.58039f },
  {   0.93725f,   0.94118f,   0.79608f },
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
