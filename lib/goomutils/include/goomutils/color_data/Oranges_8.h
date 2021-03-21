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
static const std::vector<vivid::srgb_t> Oranges_8
{
  {   1.00000f,   0.96078f,   0.92157f },
  {   0.99608f,   0.90196f,   0.80784f },
  {   0.99216f,   0.81569f,   0.63529f },
  {   0.99216f,   0.68235f,   0.41961f },
  {   0.99216f,   0.55294f,   0.23529f },
  {   0.94510f,   0.41176f,   0.07451f },
  {   0.85098f,   0.28235f,   0.00392f },
  {   0.54902f,   0.17647f,   0.01569f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
