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
static const std::vector<vivid::srgb_t> RdPu_4
{
  {   0.99608f,   0.92157f,   0.88627f },
  {   0.98431f,   0.70588f,   0.72549f },
  {   0.96863f,   0.40784f,   0.63137f },
  {   0.68235f,   0.00392f,   0.49412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
