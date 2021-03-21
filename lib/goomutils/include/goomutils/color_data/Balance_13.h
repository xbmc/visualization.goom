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
static const std::vector<vivid::srgb_t> Balance_13
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.16078f,   0.21961f,   0.53333f },
  {   0.04706f,   0.36863f,   0.74510f },
  {   0.21961f,   0.53333f,   0.72941f },
  {   0.45882f,   0.66667f,   0.74510f },
  {   0.71373f,   0.78824f,   0.81176f },
  {   0.94510f,   0.92549f,   0.92157f },
  {   0.87451f,   0.73333f,   0.69020f },
  {   0.81569f,   0.54510f,   0.45098f },
  {   0.75294f,   0.35294f,   0.23529f },
  {   0.65490f,   0.14118f,   0.14118f },
  {   0.45098f,   0.05490f,   0.15294f },
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
