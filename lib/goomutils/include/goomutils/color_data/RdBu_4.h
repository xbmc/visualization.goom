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
static const std::vector<vivid::srgb_t> RdBu_4
{
  {   0.79216f,   0.00000f,   0.12549f },
  {   0.95686f,   0.64706f,   0.50980f },
  {   0.57255f,   0.77255f,   0.87059f },
  {   0.01961f,   0.44314f,   0.69020f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
