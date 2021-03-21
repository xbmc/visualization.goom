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
static const std::vector<vivid::srgb_t> Lisbon_20
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.76471f,   0.80000f,   0.91765f },
  {   0.61961f,   0.69412f,   0.83137f },
  {   0.48627f,   0.59608f,   0.75294f },
  {   0.34902f,   0.49020f,   0.66275f },
  {   0.22745f,   0.39216f,   0.56863f },
  {   0.13333f,   0.29020f,   0.44314f },
  {   0.09020f,   0.21176f,   0.32549f },
  {   0.07059f,   0.14118f,   0.21569f },
  {   0.07451f,   0.09804f,   0.12549f },
  {   0.10980f,   0.10980f,   0.09020f },
  {   0.18824f,   0.17647f,   0.11765f },
  {   0.27451f,   0.25882f,   0.16471f },
  {   0.36863f,   0.34510f,   0.21961f },
  {   0.47451f,   0.44706f,   0.28627f },
  {   0.58039f,   0.54510f,   0.35686f },
  {   0.69412f,   0.66275f,   0.45882f },
  {   0.79608f,   0.77255f,   0.57647f },
  {   0.90196f,   0.89020f,   0.71373f },
  {   1.00000f,   1.00000f,   0.85098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
