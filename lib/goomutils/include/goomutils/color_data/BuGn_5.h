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
static const std::vector<vivid::srgb_t> BuGn_5
{
  {   0.92941f,   0.97255f,   0.98431f },
  {   0.69804f,   0.88627f,   0.88627f },
  {   0.40000f,   0.76078f,   0.64314f },
  {   0.17255f,   0.63529f,   0.37255f },
  {   0.00000f,   0.42745f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
