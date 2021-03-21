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
static const std::vector<vivid::srgb_t> OrYel_4
{
  {   0.92549f,   0.85490f,   0.60392f },
  {   0.95294f,   0.67843f,   0.41569f },
  {   0.97647f,   0.48235f,   0.34118f },
  {   0.93333f,   0.30196f,   0.35294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
