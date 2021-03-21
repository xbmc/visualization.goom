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
static const std::vector<vivid::srgb_t> Amp_12
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.90196f,   0.82353f,   0.80000f },
  {   0.86667f,   0.71765f,   0.67059f },
  {   0.83529f,   0.61176f,   0.53333f },
  {   0.80392f,   0.50588f,   0.40784f },
  {   0.77255f,   0.40392f,   0.28627f },
  {   0.73333f,   0.29020f,   0.18824f },
  {   0.67843f,   0.17255f,   0.14118f },
  {   0.59216f,   0.07843f,   0.15686f },
  {   0.47059f,   0.05490f,   0.15686f },
  {   0.35294f,   0.05490f,   0.12157f },
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
