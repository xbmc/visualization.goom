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
static const std::vector<vivid::srgb_t> Fall_7
{
  {   0.23922f,   0.34902f,   0.25490f },
  {   0.46667f,   0.53333f,   0.40784f },
  {   0.70980f,   0.72549f,   0.56863f },
  {   0.96471f,   0.92941f,   0.74118f },
  {   0.92941f,   0.73333f,   0.54118f },
  {   0.87059f,   0.54118f,   0.35294f },
  {   0.79216f,   0.33725f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
