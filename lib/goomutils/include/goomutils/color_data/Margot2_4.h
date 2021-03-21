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
static const std::vector<vivid::srgb_t> Margot2_4
{
  {   0.46275f,   0.54510f,   0.57647f },
  {   0.73725f,   0.14118f,   0.05882f },
  {   0.97647f,   0.92549f,   0.77255f },
  {   0.83137f,   0.45098f,   0.16078f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
