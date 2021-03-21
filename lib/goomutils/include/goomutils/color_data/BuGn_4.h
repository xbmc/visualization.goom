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
static const std::vector<vivid::srgb_t> BuGn_4
{
  {   0.92941f,   0.97255f,   0.98431f },
  {   0.69804f,   0.88627f,   0.88627f },
  {   0.40000f,   0.76078f,   0.64314f },
  {   0.13725f,   0.54510f,   0.27059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
