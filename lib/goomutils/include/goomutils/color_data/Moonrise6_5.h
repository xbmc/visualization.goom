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
static const std::vector<vivid::srgb_t> Moonrise6_5
{
  {   0.74902f,   0.31765f,   0.23922f },
  {   0.78824f,   0.63529f,   0.58824f },
  {   0.77255f,   0.75686f,   0.53333f },
  {   0.48235f,   0.69412f,   0.56863f },
  {   0.85098f,   0.68235f,   0.18824f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
