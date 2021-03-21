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
static const std::vector<vivid::srgb_t> Amp_15
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.90980f,   0.84706f,   0.82745f },
  {   0.88235f,   0.76471f,   0.72549f },
  {   0.85490f,   0.67843f,   0.61961f },
  {   0.83137f,   0.59608f,   0.51765f },
  {   0.80784f,   0.51765f,   0.41569f },
  {   0.78039f,   0.43529f,   0.32157f },
  {   0.75294f,   0.34510f,   0.23137f },
  {   0.71765f,   0.25490f,   0.16471f },
  {   0.67059f,   0.16471f,   0.14118f },
  {   0.60392f,   0.08627f,   0.15294f },
  {   0.51765f,   0.05490f,   0.16078f },
  {   0.41961f,   0.05882f,   0.14510f },
  {   0.32549f,   0.05098f,   0.11373f },
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
