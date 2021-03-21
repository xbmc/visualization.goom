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
static const std::vector<vivid::srgb_t> BuPu_4
{
  {   0.92941f,   0.97255f,   0.98431f },
  {   0.70196f,   0.80392f,   0.89020f },
  {   0.54902f,   0.58824f,   0.77647f },
  {   0.53333f,   0.25490f,   0.61569f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
