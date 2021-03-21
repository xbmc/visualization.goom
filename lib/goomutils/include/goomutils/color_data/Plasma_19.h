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
static const std::vector<vivid::srgb_t> Plasma_19
{
  {   0.05098f,   0.03137f,   0.52941f },
  {   0.18039f,   0.01961f,   0.58431f },
  {   0.27451f,   0.01176f,   0.62353f },
  {   0.36078f,   0.00392f,   0.65098f },
  {   0.45490f,   0.00392f,   0.65882f },
  {   0.53333f,   0.03137f,   0.65098f },
  {   0.61176f,   0.09020f,   0.61961f },
  {   0.67843f,   0.15294f,   0.57647f },
  {   0.74118f,   0.21569f,   0.52549f },
  {   0.80000f,   0.27843f,   0.47059f },
  {   0.84706f,   0.34118f,   0.41961f },
  {   0.89020f,   0.40784f,   0.37255f },
  {   0.92941f,   0.47451f,   0.32549f },
  {   0.96078f,   0.54510f,   0.27843f },
  {   0.98039f,   0.61961f,   0.23137f },
  {   0.99216f,   0.69804f,   0.18431f },
  {   0.99216f,   0.79216f,   0.14902f },
  {   0.97255f,   0.88235f,   0.14510f },
  {   0.94118f,   0.97647f,   0.12941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
