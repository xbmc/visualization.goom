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
static const std::vector<vivid::srgb_t> Davos_5
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.18431f,   0.35294f,   0.58824f },
  {   0.42353f,   0.55686f,   0.57647f },
  {   0.73333f,   0.78039f,   0.58039f },
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
