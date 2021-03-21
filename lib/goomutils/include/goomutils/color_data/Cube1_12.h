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
static const std::vector<vivid::srgb_t> Cube1_12
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.50980f,   0.10980f,   0.77255f },
  {   0.45098f,   0.34902f,   0.97647f },
  {   0.36078f,   0.52941f,   0.94118f },
  {   0.25098f,   0.66667f,   0.79216f },
  {   0.25490f,   0.77255f,   0.60392f },
  {   0.31765f,   0.84706f,   0.39608f },
  {   0.43529f,   0.90980f,   0.29804f },
  {   0.66275f,   0.92549f,   0.33725f },
  {   0.82353f,   0.91765f,   0.35686f },
  {   0.92941f,   0.78824f,   0.36863f },
  {   0.97647f,   0.58824f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
