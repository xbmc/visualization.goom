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
static const std::vector<vivid::srgb_t> Oxy_17
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.35686f,   0.02745f,   0.04706f },
  {   0.46275f,   0.01961f,   0.05882f },
  {   0.55294f,   0.08235f,   0.03137f },
  {   0.36078f,   0.35686f,   0.35686f },
  {   0.41961f,   0.41569f,   0.41569f },
  {   0.47843f,   0.47843f,   0.47451f },
  {   0.54118f,   0.54118f,   0.53725f },
  {   0.60784f,   0.60392f,   0.60392f },
  {   0.67059f,   0.67059f,   0.66667f },
  {   0.74118f,   0.74118f,   0.73725f },
  {   0.81569f,   0.81569f,   0.81176f },
  {   0.89412f,   0.89412f,   0.89020f },
  {   0.95686f,   0.98824f,   0.38431f },
  {   0.91373f,   0.89020f,   0.20392f },
  {   0.89412f,   0.78431f,   0.14510f },
  {   0.86667f,   0.68627f,   0.09804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
