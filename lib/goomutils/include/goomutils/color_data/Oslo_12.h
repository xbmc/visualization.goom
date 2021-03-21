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
static const std::vector<vivid::srgb_t> Oslo_12
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.05098f,   0.09020f,   0.13725f },
  {   0.06275f,   0.16078f,   0.25490f },
  {   0.09412f,   0.24314f,   0.39216f },
  {   0.14118f,   0.32941f,   0.53333f },
  {   0.23922f,   0.42353f,   0.67451f },
  {   0.38039f,   0.52941f,   0.77255f },
  {   0.49804f,   0.60784f,   0.79216f },
  {   0.60392f,   0.67451f,   0.78824f },
  {   0.72549f,   0.75686f,   0.80392f },
  {   0.85882f,   0.86667f,   0.87843f },
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
