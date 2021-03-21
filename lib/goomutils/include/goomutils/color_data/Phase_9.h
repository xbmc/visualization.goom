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
static const std::vector<vivid::srgb_t> Phase_9
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.81176f,   0.33725f,   0.26275f },
  {   0.87451f,   0.16471f,   0.57647f },
  {   0.75294f,   0.25490f,   0.89804f },
  {   0.49020f,   0.45098f,   0.94118f },
  {   0.18039f,   0.56078f,   0.74510f },
  {   0.04706f,   0.59608f,   0.49412f },
  {   0.35294f,   0.58039f,   0.13725f },
  {   0.65882f,   0.47059f,   0.05098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
