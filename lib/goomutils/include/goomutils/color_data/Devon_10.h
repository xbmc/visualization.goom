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
static const std::vector<vivid::srgb_t> Devon_10
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16078f,   0.20392f,   0.40392f },
  {   0.15294f,   0.31765f,   0.52549f },
  {   0.21176f,   0.41176f,   0.67843f },
  {   0.38039f,   0.50588f,   0.81569f },
  {   0.59608f,   0.60784f,   0.90588f },
  {   0.72941f,   0.70196f,   0.94510f },
  {   0.81569f,   0.80000f,   0.96078f },
  {   0.90980f,   0.89804f,   0.98039f },
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
