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
static const std::vector<vivid::srgb_t> red_16
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.07451f,   0.04706f,   0.13725f },
  {   0.17255f,   0.08627f,   0.25490f },
  {   0.28627f,   0.12549f,   0.35294f },
  {   0.40784f,   0.16078f,   0.41961f },
  {   0.52549f,   0.20784f,   0.46275f },
  {   0.63529f,   0.26275f,   0.48627f },
  {   0.72549f,   0.32549f,   0.49412f },
  {   0.80000f,   0.40000f,   0.50196f },
  {   0.84706f,   0.48627f,   0.50980f },
  {   0.88235f,   0.58039f,   0.53333f },
  {   0.89804f,   0.67451f,   0.57647f },
  {   0.90980f,   0.76863f,   0.64314f },
  {   0.92549f,   0.85882f,   0.74118f },
  {   0.94902f,   0.93333f,   0.85882f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
