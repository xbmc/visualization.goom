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
static const std::vector<vivid::srgb_t> PurpleGray_12
{
  {   0.48235f,   0.40000f,   0.82353f },
  {   0.65098f,   0.60000f,   0.90980f },
  {   0.86275f,   0.37255f,   0.74118f },
  {   1.00000f,   0.75294f,   0.85490f },
  {   0.37255f,   0.35294f,   0.25490f },
  {   0.70588f,   0.69412f,   0.60784f },
  {   0.60000f,   0.33725f,   0.53333f },
  {   0.84706f,   0.59608f,   0.72941f },
  {   0.67059f,   0.41569f,   0.83529f },
  {   0.81569f,   0.59608f,   0.93333f },
  {   0.54510f,   0.48627f,   0.43137f },
  {   0.85882f,   0.83137f,   0.77255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
