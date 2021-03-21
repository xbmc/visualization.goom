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
static const std::vector<vivid::srgb_t> Oxy_18
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.34510f,   0.02745f,   0.04314f },
  {   0.44706f,   0.02353f,   0.05882f },
  {   0.53725f,   0.06275f,   0.03922f },
  {   0.34510f,   0.34118f,   0.34118f },
  {   0.40000f,   0.40000f,   0.39608f },
  {   0.45490f,   0.45098f,   0.45098f },
  {   0.51373f,   0.51373f,   0.50980f },
  {   0.57255f,   0.57255f,   0.56863f },
  {   0.63922f,   0.63529f,   0.63137f },
  {   0.70196f,   0.70196f,   0.69804f },
  {   0.77255f,   0.77255f,   0.76471f },
  {   0.83922f,   0.83922f,   0.83529f },
  {   0.91765f,   0.91373f,   0.90980f },
  {   0.93725f,   0.97255f,   0.34118f },
  {   0.90980f,   0.87451f,   0.19216f },
  {   0.89020f,   0.77647f,   0.13725f },
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
