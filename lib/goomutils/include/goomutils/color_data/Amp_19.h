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
static const std::vector<vivid::srgb_t> Amp_19
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.91765f,   0.86275f,   0.85098f },
  {   0.89412f,   0.80000f,   0.77255f },
  {   0.87451f,   0.73725f,   0.69020f },
  {   0.85098f,   0.66667f,   0.60784f },
  {   0.83529f,   0.60392f,   0.52941f },
  {   0.81569f,   0.54510f,   0.45098f },
  {   0.79608f,   0.47843f,   0.37647f },
  {   0.77647f,   0.41569f,   0.30196f },
  {   0.75294f,   0.34510f,   0.23137f },
  {   0.72549f,   0.27451f,   0.17647f },
  {   0.69412f,   0.20392f,   0.14510f },
  {   0.65098f,   0.13333f,   0.14510f },
  {   0.59608f,   0.08235f,   0.15294f },
  {   0.52941f,   0.05490f,   0.16078f },
  {   0.45490f,   0.05490f,   0.15686f },
  {   0.37647f,   0.05490f,   0.13333f },
  {   0.30588f,   0.05098f,   0.10196f },
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
