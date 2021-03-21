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
static const std::vector<vivid::srgb_t> Solar_16
{
  {   0.20000f,   0.07843f,   0.09412f },
  {   0.28235f,   0.10588f,   0.12157f },
  {   0.36863f,   0.12941f,   0.14118f },
  {   0.45098f,   0.15294f,   0.14118f },
  {   0.52941f,   0.18431f,   0.12941f },
  {   0.59216f,   0.23137f,   0.10980f },
  {   0.64706f,   0.29020f,   0.09020f },
  {   0.69412f,   0.35686f,   0.07843f },
  {   0.73333f,   0.42745f,   0.07451f },
  {   0.76863f,   0.49804f,   0.08235f },
  {   0.79608f,   0.57255f,   0.10196f },
  {   0.82353f,   0.65098f,   0.12941f },
  {   0.84706f,   0.72941f,   0.16471f },
  {   0.86275f,   0.81569f,   0.20392f },
  {   0.87451f,   0.90196f,   0.24706f },
  {   0.88235f,   0.99216f,   0.29412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
