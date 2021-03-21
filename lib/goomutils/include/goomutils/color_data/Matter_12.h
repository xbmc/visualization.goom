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
static const std::vector<vivid::srgb_t> Matter_12
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98039f,   0.80392f,   0.57255f },
  {   0.96471f,   0.68235f,   0.47059f },
  {   0.94118f,   0.55294f,   0.38431f },
  {   0.90588f,   0.43137f,   0.33333f },
  {   0.85098f,   0.31373f,   0.32549f },
  {   0.76471f,   0.22353f,   0.35294f },
  {   0.66275f,   0.15686f,   0.38039f },
  {   0.54902f,   0.11765f,   0.38824f },
  {   0.41961f,   0.09804f,   0.36863f },
  {   0.30196f,   0.08235f,   0.31765f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
