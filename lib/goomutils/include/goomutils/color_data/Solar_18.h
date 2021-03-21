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
static const std::vector<vivid::srgb_t> Solar_18
{
  {   0.20000f,   0.07843f,   0.09412f },
  {   0.27451f,   0.10196f,   0.12157f },
  {   0.34902f,   0.12157f,   0.13725f },
  {   0.41961f,   0.14118f,   0.14510f },
  {   0.49412f,   0.16863f,   0.13725f },
  {   0.55686f,   0.20392f,   0.12157f },
  {   0.60784f,   0.25098f,   0.10196f },
  {   0.65490f,   0.30196f,   0.09020f },
  {   0.69412f,   0.36078f,   0.07843f },
  {   0.72941f,   0.42353f,   0.07451f },
  {   0.76078f,   0.48627f,   0.07843f },
  {   0.78824f,   0.54902f,   0.09412f },
  {   0.81569f,   0.61961f,   0.11765f },
  {   0.83529f,   0.68627f,   0.14510f },
  {   0.85098f,   0.76078f,   0.18039f },
  {   0.86667f,   0.83529f,   0.21569f },
  {   0.87451f,   0.91373f,   0.25490f },
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
