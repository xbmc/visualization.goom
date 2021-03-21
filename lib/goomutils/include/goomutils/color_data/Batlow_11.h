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
static const std::vector<vivid::srgb_t> Batlow_11
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.05098f,   0.20392f,   0.36863f },
  {   0.09412f,   0.30980f,   0.38039f },
  {   0.19608f,   0.40000f,   0.35686f },
  {   0.34118f,   0.46275f,   0.27843f },
  {   0.50588f,   0.50980f,   0.20000f },
  {   0.69804f,   0.55294f,   0.19608f },
  {   0.89020f,   0.59608f,   0.33725f },
  {   0.98824f,   0.65490f,   0.55294f },
  {   0.99216f,   0.72549f,   0.76863f },
  {   0.98039f,   0.80000f,   0.98039f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
