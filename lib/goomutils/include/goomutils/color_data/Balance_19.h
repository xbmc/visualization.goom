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
static const std::vector<vivid::srgb_t> Balance_19
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.14510f,   0.18431f,   0.43529f },
  {   0.16078f,   0.25882f,   0.63529f },
  {   0.04706f,   0.36863f,   0.74510f },
  {   0.14902f,   0.48235f,   0.72941f },
  {   0.29412f,   0.58039f,   0.72941f },
  {   0.45882f,   0.66667f,   0.74510f },
  {   0.63137f,   0.74510f,   0.78431f },
  {   0.79216f,   0.83137f,   0.84706f },
  {   0.94510f,   0.92549f,   0.92157f },
  {   0.89412f,   0.79608f,   0.76863f },
  {   0.85490f,   0.67059f,   0.60784f },
  {   0.81569f,   0.54510f,   0.45098f },
  {   0.77647f,   0.41961f,   0.30196f },
  {   0.72941f,   0.28235f,   0.18039f },
  {   0.65490f,   0.14118f,   0.14118f },
  {   0.52549f,   0.05490f,   0.16078f },
  {   0.37647f,   0.05490f,   0.13333f },
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
