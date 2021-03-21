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
static const std::vector<vivid::srgb_t> Vik_13
{
  {   0.00000f,   0.07059f,   0.38039f },
  {   0.00784f,   0.20000f,   0.46275f },
  {   0.02353f,   0.32941f,   0.54510f },
  {   0.18824f,   0.49020f,   0.65098f },
  {   0.44314f,   0.65882f,   0.76863f },
  {   0.70196f,   0.81961f,   0.87451f },
  {   0.92549f,   0.89804f,   0.87843f },
  {   0.89412f,   0.74902f,   0.66667f },
  {   0.82745f,   0.59216f,   0.45490f },
  {   0.76471f,   0.44706f,   0.26275f },
  {   0.67059f,   0.28235f,   0.07843f },
  {   0.49412f,   0.11373f,   0.02353f },
  {   0.34902f,   0.00000f,   0.03137f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
