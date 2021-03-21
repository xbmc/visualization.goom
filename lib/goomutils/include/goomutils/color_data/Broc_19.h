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
static const std::vector<vivid::srgb_t> Broc_19
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.18039f,   0.38039f },
  {   0.15686f,   0.26667f,   0.46667f },
  {   0.18824f,   0.36078f,   0.54902f },
  {   0.29412f,   0.46275f,   0.62745f },
  {   0.41961f,   0.55686f,   0.69412f },
  {   0.54510f,   0.65490f,   0.76078f },
  {   0.67451f,   0.75294f,   0.82745f },
  {   0.80784f,   0.85098f,   0.89804f },
  {   0.92157f,   0.93333f,   0.92549f },
  {   0.90980f,   0.90980f,   0.82353f },
  {   0.84706f,   0.84706f,   0.69412f },
  {   0.77255f,   0.77255f,   0.56078f },
  {   0.66667f,   0.66667f,   0.43529f },
  {   0.55294f,   0.55294f,   0.33725f },
  {   0.44706f,   0.44706f,   0.24706f },
  {   0.33333f,   0.33333f,   0.15294f },
  {   0.23529f,   0.23922f,   0.07843f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
