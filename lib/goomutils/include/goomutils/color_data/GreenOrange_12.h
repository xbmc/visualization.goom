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
static const std::vector<vivid::srgb_t> GreenOrange_12
{
  {   0.19608f,   0.63529f,   0.31765f },
  {   0.67451f,   0.85098f,   0.55294f },
  {   1.00000f,   0.49804f,   0.05882f },
  {   1.00000f,   0.72549f,   0.46667f },
  {   0.23529f,   0.71765f,   0.80000f },
  {   0.59608f,   0.85098f,   0.89412f },
  {   0.72157f,   0.35294f,   0.05098f },
  {   1.00000f,   0.85098f,   0.29020f },
  {   0.22353f,   0.45098f,   0.48627f },
  {   0.52549f,   0.70588f,   0.66275f },
  {   0.50980f,   0.52157f,   0.23137f },
  {   0.80000f,   0.78824f,   0.30196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
