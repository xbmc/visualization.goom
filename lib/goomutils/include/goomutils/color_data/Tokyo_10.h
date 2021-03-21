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
static const std::vector<vivid::srgb_t> Tokyo_10
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.27059f,   0.12549f,   0.29804f },
  {   0.43137f,   0.24314f,   0.40392f },
  {   0.52157f,   0.36863f,   0.47059f },
  {   0.55294f,   0.47451f,   0.50980f },
  {   0.57255f,   0.58039f,   0.53725f },
  {   0.59216f,   0.68235f,   0.56863f },
  {   0.65490f,   0.80784f,   0.61569f },
  {   0.83529f,   0.94902f,   0.73725f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
