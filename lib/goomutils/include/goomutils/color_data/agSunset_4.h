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
static const std::vector<vivid::srgb_t> agSunset_4
{
  {   0.29412f,   0.16078f,   0.56863f },
  {   0.75294f,   0.21176f,   0.61569f },
  {   0.98039f,   0.47059f,   0.46275f },
  {   0.92941f,   0.85098f,   0.63922f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
