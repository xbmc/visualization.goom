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
static const std::vector<vivid::srgb_t> BlueOrange8_6
{
  {   0.00000f,   0.49804f,   1.00000f },
  {   0.29804f,   0.76471f,   1.00000f },
  {   0.80000f,   1.00000f,   1.00000f },
  {   1.00000f,   1.00000f,   0.80000f },
  {   1.00000f,   0.76471f,   0.29804f },
  {   1.00000f,   0.49804f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
