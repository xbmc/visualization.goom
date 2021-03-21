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
static const std::vector<vivid::srgb_t> BuPu_7
{
  {   0.92941f,   0.97255f,   0.98431f },
  {   0.74902f,   0.82745f,   0.90196f },
  {   0.61961f,   0.73725f,   0.85490f },
  {   0.54902f,   0.58824f,   0.77647f },
  {   0.54902f,   0.41961f,   0.69412f },
  {   0.53333f,   0.25490f,   0.61569f },
  {   0.43137f,   0.00392f,   0.41961f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
