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
static const std::vector<vivid::srgb_t> BuPu_9
{
  {   0.96863f,   0.98824f,   0.99216f },
  {   0.87843f,   0.92549f,   0.95686f },
  {   0.74902f,   0.82745f,   0.90196f },
  {   0.61961f,   0.73725f,   0.85490f },
  {   0.54902f,   0.58824f,   0.77647f },
  {   0.54902f,   0.41961f,   0.69412f },
  {   0.53333f,   0.25490f,   0.61569f },
  {   0.50588f,   0.05882f,   0.48627f },
  {   0.30196f,   0.00000f,   0.29412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
