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
static const std::vector<vivid::srgb_t> Phase_18
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.74118f,   0.41176f,   0.14902f },
  {   0.80392f,   0.34510f,   0.24706f },
  {   0.85098f,   0.27059f,   0.36863f },
  {   0.87451f,   0.18431f,   0.52941f },
  {   0.85490f,   0.14902f,   0.71373f },
  {   0.78824f,   0.21569f,   0.85882f },
  {   0.69020f,   0.31373f,   0.93725f },
  {   0.56863f,   0.40784f,   0.95686f },
  {   0.41961f,   0.48235f,   0.91373f },
  {   0.25882f,   0.54118f,   0.81961f },
  {   0.14118f,   0.57255f,   0.69804f },
  {   0.08235f,   0.58824f,   0.58039f },
  {   0.04314f,   0.60000f,   0.45882f },
  {   0.16863f,   0.60392f,   0.29804f },
  {   0.38039f,   0.57647f,   0.11765f },
  {   0.54510f,   0.52549f,   0.05098f },
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
