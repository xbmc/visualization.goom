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
static const std::vector<vivid::srgb_t> YlOrBr_9
{
  {   1.00000f,   1.00000f,   0.89804f },
  {   1.00000f,   0.96863f,   0.73725f },
  {   0.99608f,   0.89020f,   0.56863f },
  {   0.99608f,   0.76863f,   0.30980f },
  {   0.99608f,   0.60000f,   0.16078f },
  {   0.92549f,   0.43922f,   0.07843f },
  {   0.80000f,   0.29804f,   0.00784f },
  {   0.60000f,   0.20392f,   0.01569f },
  {   0.40000f,   0.14510f,   0.02353f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
