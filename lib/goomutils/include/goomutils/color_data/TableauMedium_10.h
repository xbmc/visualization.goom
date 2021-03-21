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
static const std::vector<vivid::srgb_t> TableauMedium_10
{
  {   0.44706f,   0.61961f,   0.80784f },
  {   1.00000f,   0.61961f,   0.29020f },
  {   0.40392f,   0.74902f,   0.36078f },
  {   0.92941f,   0.40000f,   0.36471f },
  {   0.67843f,   0.54510f,   0.78824f },
  {   0.65882f,   0.47059f,   0.43137f },
  {   0.92941f,   0.59216f,   0.79216f },
  {   0.63529f,   0.63529f,   0.63529f },
  {   0.80392f,   0.80000f,   0.36471f },
  {   0.42745f,   0.80000f,   0.85490f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
