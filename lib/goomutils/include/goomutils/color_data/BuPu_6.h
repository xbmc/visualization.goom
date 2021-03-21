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
static const std::vector<vivid::srgb_t> BuPu_6
{
  {   0.92941f,   0.97255f,   0.98431f },
  {   0.74902f,   0.82745f,   0.90196f },
  {   0.61961f,   0.73725f,   0.85490f },
  {   0.54902f,   0.58824f,   0.77647f },
  {   0.53333f,   0.33725f,   0.65490f },
  {   0.50588f,   0.05882f,   0.48627f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
