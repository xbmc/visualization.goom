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
static const std::vector<vivid::srgb_t> YlOrRd_4
{
  {   1.00000f,   1.00000f,   0.69804f },
  {   0.99608f,   0.80000f,   0.36078f },
  {   0.99216f,   0.55294f,   0.23529f },
  {   0.89020f,   0.10196f,   0.10980f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
