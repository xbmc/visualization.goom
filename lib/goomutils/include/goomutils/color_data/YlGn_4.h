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
static const std::vector<vivid::srgb_t> YlGn_4
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.76078f,   0.90196f,   0.60000f },
  {   0.47059f,   0.77647f,   0.47451f },
  {   0.13725f,   0.51765f,   0.26275f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
