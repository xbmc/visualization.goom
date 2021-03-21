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
static const std::vector<vivid::srgb_t> Oxy_19
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.34118f,   0.02745f,   0.04314f },
  {   0.43529f,   0.02353f,   0.05882f },
  {   0.52157f,   0.03922f,   0.04314f },
  {   0.33333f,   0.32941f,   0.32941f },
  {   0.38431f,   0.38431f,   0.38039f },
  {   0.43529f,   0.43529f,   0.43137f },
  {   0.49020f,   0.49020f,   0.48627f },
  {   0.54510f,   0.54510f,   0.54118f },
  {   0.60784f,   0.60392f,   0.60392f },
  {   0.66667f,   0.66667f,   0.66275f },
  {   0.72941f,   0.72549f,   0.72157f },
  {   0.79608f,   0.79216f,   0.78824f },
  {   0.85882f,   0.85882f,   0.85490f },
  {   0.93333f,   0.93333f,   0.92549f },
  {   0.92549f,   0.96078f,   0.30588f },
  {   0.90980f,   0.86275f,   0.18824f },
  {   0.89020f,   0.76863f,   0.13725f },
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
