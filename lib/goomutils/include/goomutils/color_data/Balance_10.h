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
static const std::vector<vivid::srgb_t> Balance_10
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.16078f,   0.25882f,   0.63529f },
  {   0.14902f,   0.48235f,   0.72941f },
  {   0.45882f,   0.66667f,   0.74510f },
  {   0.79216f,   0.83137f,   0.84706f },
  {   0.89412f,   0.79608f,   0.76863f },
  {   0.81569f,   0.54510f,   0.45098f },
  {   0.72941f,   0.28235f,   0.18039f },
  {   0.52549f,   0.05490f,   0.16078f },
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
