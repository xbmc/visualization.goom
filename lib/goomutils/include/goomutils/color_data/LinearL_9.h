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
static const std::vector<vivid::srgb_t> LinearL_9
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.17647f,   0.09020f,   0.27843f },
  {   0.10588f,   0.22353f,   0.49804f },
  {   0.00000f,   0.39216f,   0.42745f },
  {   0.00000f,   0.55686f,   0.24706f },
  {   0.20392f,   0.69412f,   0.00000f },
  {   0.67451f,   0.77647f,   0.00000f },
  {   0.96078f,   0.83922f,   0.71765f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
