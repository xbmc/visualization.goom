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
static const std::vector<vivid::srgb_t> LinearL_17
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.14118f,   0.05490f,   0.12549f },
  {   0.17647f,   0.09020f,   0.27843f },
  {   0.17255f,   0.13333f,   0.45490f },
  {   0.10588f,   0.22353f,   0.49804f },
  {   0.06667f,   0.30588f,   0.50588f },
  {   0.00000f,   0.39216f,   0.42745f },
  {   0.00000f,   0.47451f,   0.34510f },
  {   0.00000f,   0.55686f,   0.24706f },
  {   0.00000f,   0.63529f,   0.17255f },
  {   0.20392f,   0.69412f,   0.00000f },
  {   0.36078f,   0.75686f,   0.00000f },
  {   0.67451f,   0.77647f,   0.00000f },
  {   0.84314f,   0.80392f,   0.42745f },
  {   0.96078f,   0.83922f,   0.71765f },
  {   0.96863f,   0.92157f,   0.88235f },
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
