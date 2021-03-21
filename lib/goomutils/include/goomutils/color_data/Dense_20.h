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
static const std::vector<vivid::srgb_t> Dense_20
{
  {   0.90196f,   0.94510f,   0.94510f },
  {   0.81569f,   0.90196f,   0.91373f },
  {   0.72549f,   0.85490f,   0.89412f },
  {   0.64706f,   0.81176f,   0.88627f },
  {   0.57255f,   0.76471f,   0.88627f },
  {   0.51373f,   0.71373f,   0.89020f },
  {   0.47059f,   0.65882f,   0.89412f },
  {   0.45490f,   0.60392f,   0.89412f },
  {   0.45490f,   0.54118f,   0.88627f },
  {   0.46275f,   0.47451f,   0.85490f },
  {   0.47059f,   0.41569f,   0.81569f },
  {   0.47451f,   0.35294f,   0.75686f },
  {   0.47059f,   0.29804f,   0.69412f },
  {   0.45882f,   0.24314f,   0.62353f },
  {   0.43922f,   0.19216f,   0.54118f },
  {   0.41569f,   0.14902f,   0.45882f },
  {   0.37647f,   0.10980f,   0.36863f },
  {   0.33333f,   0.08627f,   0.28627f },
  {   0.27451f,   0.07059f,   0.20392f },
  {   0.21176f,   0.05490f,   0.14118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
