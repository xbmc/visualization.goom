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
static const std::vector<vivid::srgb_t> Davos_14
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.04314f,   0.13333f,   0.40392f },
  {   0.10196f,   0.23137f,   0.49804f },
  {   0.16471f,   0.32941f,   0.57647f },
  {   0.23529f,   0.41176f,   0.61176f },
  {   0.31373f,   0.47843f,   0.61176f },
  {   0.38824f,   0.53333f,   0.59216f },
  {   0.45490f,   0.57647f,   0.56078f },
  {   0.53725f,   0.63137f,   0.53333f },
  {   0.63922f,   0.70588f,   0.53725f },
  {   0.77255f,   0.81176f,   0.60784f },
  {   0.90588f,   0.91765f,   0.74510f },
  {   0.97255f,   0.97255f,   0.87843f },
  {   0.99608f,   0.99608f,   0.99608f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
