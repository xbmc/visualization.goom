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
static const std::vector<vivid::srgb_t> Oxy_20
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.33333f,   0.02745f,   0.04314f },
  {   0.42745f,   0.02353f,   0.05882f },
  {   0.51373f,   0.03137f,   0.04706f },
  {   0.32157f,   0.31765f,   0.31765f },
  {   0.37255f,   0.36863f,   0.36863f },
  {   0.41961f,   0.41961f,   0.41569f },
  {   0.47059f,   0.46667f,   0.46667f },
  {   0.52157f,   0.52157f,   0.51765f },
  {   0.57647f,   0.57647f,   0.57255f },
  {   0.63529f,   0.63137f,   0.62745f },
  {   0.69412f,   0.69020f,   0.68627f },
  {   0.75294f,   0.75294f,   0.74902f },
  {   0.81176f,   0.81176f,   0.80784f },
  {   0.87843f,   0.87843f,   0.87451f },
  {   0.94902f,   0.94902f,   0.94510f },
  {   0.91765f,   0.94510f,   0.27059f },
  {   0.90980f,   0.85098f,   0.18039f },
  {   0.89020f,   0.76471f,   0.13333f },
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
