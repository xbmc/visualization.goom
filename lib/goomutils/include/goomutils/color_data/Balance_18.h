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
static const std::vector<vivid::srgb_t> Balance_18
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.14510f,   0.18824f,   0.45098f },
  {   0.15294f,   0.27059f,   0.66275f },
  {   0.03922f,   0.39216f,   0.74510f },
  {   0.18039f,   0.50588f,   0.72941f },
  {   0.33725f,   0.60392f,   0.73333f },
  {   0.52157f,   0.69412f,   0.75294f },
  {   0.70196f,   0.78039f,   0.80784f },
  {   0.87059f,   0.87843f,   0.88235f },
  {   0.91765f,   0.86275f,   0.84706f },
  {   0.87059f,   0.72549f,   0.67843f },
  {   0.82745f,   0.58824f,   0.50588f },
  {   0.78824f,   0.45490f,   0.34510f },
  {   0.74118f,   0.31373f,   0.20392f },
  {   0.67059f,   0.16078f,   0.14118f },
  {   0.54510f,   0.05882f,   0.16078f },
  {   0.38824f,   0.05490f,   0.13725f },
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
