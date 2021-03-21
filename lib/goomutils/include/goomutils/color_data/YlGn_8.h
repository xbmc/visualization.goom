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
static const std::vector<vivid::srgb_t> YlGn_8
{
  {   1.00000f,   1.00000f,   0.89804f },
  {   0.96863f,   0.98824f,   0.72549f },
  {   0.85098f,   0.94118f,   0.63922f },
  {   0.67843f,   0.86667f,   0.55686f },
  {   0.47059f,   0.77647f,   0.47451f },
  {   0.25490f,   0.67059f,   0.36471f },
  {   0.13725f,   0.51765f,   0.26275f },
  {   0.00000f,   0.35294f,   0.19608f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
