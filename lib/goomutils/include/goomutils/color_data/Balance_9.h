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
static const std::vector<vivid::srgb_t> Balance_9
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.14510f,   0.28235f,   0.69020f },
  {   0.21961f,   0.53333f,   0.72941f },
  {   0.59608f,   0.72941f,   0.77255f },
  {   0.94510f,   0.92549f,   0.92157f },
  {   0.84706f,   0.64314f,   0.57647f },
  {   0.75294f,   0.35294f,   0.23529f },
  {   0.56471f,   0.06275f,   0.16078f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
