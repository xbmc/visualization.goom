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
static const std::vector<vivid::srgb_t> YlGnBu_4
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.63137f,   0.85490f,   0.70588f },
  {   0.25490f,   0.71373f,   0.76863f },
  {   0.13333f,   0.36863f,   0.65882f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
