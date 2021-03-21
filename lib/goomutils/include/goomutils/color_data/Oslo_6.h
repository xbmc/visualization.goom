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
static const std::vector<vivid::srgb_t> Oslo_6
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.07059f,   0.17647f,   0.28235f },
  {   0.17255f,   0.36471f,   0.58824f },
  {   0.45490f,   0.58039f,   0.78824f },
  {   0.69804f,   0.73725f,   0.80000f },
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
