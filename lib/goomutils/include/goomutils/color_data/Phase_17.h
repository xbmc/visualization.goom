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
static const std::vector<vivid::srgb_t> Phase_17
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.74510f,   0.40784f,   0.15686f },
  {   0.81176f,   0.33725f,   0.26275f },
  {   0.85882f,   0.25098f,   0.40000f },
  {   0.87451f,   0.16471f,   0.57647f },
  {   0.83529f,   0.16078f,   0.76863f },
  {   0.75294f,   0.25490f,   0.89804f },
  {   0.63529f,   0.36078f,   0.95294f },
  {   0.49020f,   0.45098f,   0.94118f },
  {   0.33333f,   0.51765f,   0.87059f },
  {   0.18039f,   0.56078f,   0.74510f },
  {   0.09804f,   0.58431f,   0.61961f },
  {   0.04706f,   0.59608f,   0.49412f },
  {   0.12941f,   0.60392f,   0.33333f },
  {   0.35294f,   0.58039f,   0.13725f },
  {   0.53333f,   0.52941f,   0.05490f },
  {   0.65882f,   0.47059f,   0.05098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
