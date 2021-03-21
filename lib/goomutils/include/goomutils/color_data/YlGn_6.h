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
static const std::vector<vivid::srgb_t> YlGn_6
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.85098f,   0.94118f,   0.63922f },
  {   0.67843f,   0.86667f,   0.55686f },
  {   0.47059f,   0.77647f,   0.47451f },
  {   0.19216f,   0.63922f,   0.32941f },
  {   0.00000f,   0.40784f,   0.21569f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
