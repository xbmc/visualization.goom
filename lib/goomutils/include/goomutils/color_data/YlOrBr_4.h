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
static const std::vector<vivid::srgb_t> YlOrBr_4
{
  {   1.00000f,   1.00000f,   0.83137f },
  {   0.99608f,   0.85098f,   0.55686f },
  {   0.99608f,   0.60000f,   0.16078f },
  {   0.80000f,   0.29804f,   0.00784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
