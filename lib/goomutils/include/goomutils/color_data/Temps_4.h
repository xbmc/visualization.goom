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
static const std::vector<vivid::srgb_t> Temps_4
{
  {   0.00000f,   0.57647f,   0.57255f },
  {   0.61176f,   0.79608f,   0.52549f },
  {   0.93333f,   0.70588f,   0.47451f },
  {   0.81176f,   0.34902f,   0.49412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
