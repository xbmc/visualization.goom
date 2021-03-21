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
static const std::vector<vivid::srgb_t> Safe_9
{
  {   0.53333f,   0.80000f,   0.93333f },
  {   0.80000f,   0.40000f,   0.46667f },
  {   0.86667f,   0.80000f,   0.46667f },
  {   0.06667f,   0.46667f,   0.20000f },
  {   0.20000f,   0.13333f,   0.53333f },
  {   0.66667f,   0.26667f,   0.60000f },
  {   0.26667f,   0.66667f,   0.60000f },
  {   0.60000f,   0.60000f,   0.20000f },
  {   0.53333f,   0.13333f,   0.33333f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
