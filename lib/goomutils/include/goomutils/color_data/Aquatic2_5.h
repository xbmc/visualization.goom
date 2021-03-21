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
static const std::vector<vivid::srgb_t> Aquatic2_5
{
  {   0.54510f,   0.61176f,   0.72157f },
  {   0.91373f,   0.89804f,   0.25490f },
  {   0.34510f,   0.62353f,   0.76078f },
  {   0.62745f,   0.55294f,   0.36863f },
  {   0.74118f,   0.72549f,   0.80784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
