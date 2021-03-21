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
static const std::vector<vivid::srgb_t> Algae_19
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.77255f,   0.92549f,   0.73333f },
  {   0.70588f,   0.87843f,   0.65882f },
  {   0.63529f,   0.83529f,   0.58431f },
  {   0.55686f,   0.78824f,   0.50980f },
  {   0.47843f,   0.74510f,   0.44706f },
  {   0.39216f,   0.70588f,   0.38824f },
  {   0.29020f,   0.67059f,   0.34118f },
  {   0.17255f,   0.62745f,   0.32157f },
  {   0.07059f,   0.58039f,   0.31373f },
  {   0.02745f,   0.52941f,   0.30196f },
  {   0.04314f,   0.48235f,   0.29020f },
  {   0.07059f,   0.43137f,   0.27059f },
  {   0.09020f,   0.38431f,   0.24706f },
  {   0.09804f,   0.33333f,   0.21961f },
  {   0.10196f,   0.28627f,   0.18824f },
  {   0.09804f,   0.23529f,   0.15294f },
  {   0.08627f,   0.18824f,   0.11765f },
  {   0.07059f,   0.14118f,   0.07843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
