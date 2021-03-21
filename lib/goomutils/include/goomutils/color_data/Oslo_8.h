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
static const std::vector<vivid::srgb_t> Oslo_8
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.05882f,   0.12941f,   0.20000f },
  {   0.09804f,   0.25490f,   0.41176f },
  {   0.20000f,   0.39216f,   0.63137f },
  {   0.41961f,   0.55686f,   0.78431f },
  {   0.59216f,   0.66275f,   0.78824f },
  {   0.78039f,   0.80000f,   0.82745f },
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
