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
static const std::vector<vivid::srgb_t> CubeYF_16
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.52549f,   0.08235f,   0.72941f },
  {   0.50980f,   0.22745f,   0.85882f },
  {   0.45098f,   0.34118f,   0.97255f },
  {   0.40784f,   0.43922f,   0.99608f },
  {   0.35294f,   0.53725f,   0.93333f },
  {   0.29804f,   0.61961f,   0.85098f },
  {   0.23529f,   0.69804f,   0.74902f },
  {   0.23922f,   0.75294f,   0.64314f },
  {   0.27843f,   0.80392f,   0.52157f },
  {   0.31765f,   0.84706f,   0.40000f },
  {   0.36078f,   0.89020f,   0.29020f },
  {   0.46275f,   0.91373f,   0.30196f },
  {   0.62353f,   0.92549f,   0.33333f },
  {   0.72157f,   0.92549f,   0.34510f },
  {   0.81961f,   0.92157f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
