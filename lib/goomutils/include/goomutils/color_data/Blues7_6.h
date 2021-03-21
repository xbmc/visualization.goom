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
static const std::vector<vivid::srgb_t> Blues7_6
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.80000f,   0.99216f,   1.00000f },
  {   0.60000f,   0.97255f,   1.00000f },
  {   0.20000f,   0.89020f,   1.00000f },
  {   0.00000f,   0.66667f,   0.80000f },
  {   0.00000f,   0.47843f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
