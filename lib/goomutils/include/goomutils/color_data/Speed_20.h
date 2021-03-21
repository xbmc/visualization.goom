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
static const std::vector<vivid::srgb_t> Speed_20
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.96471f,   0.92941f,   0.69412f },
  {   0.92941f,   0.86667f,   0.57647f },
  {   0.89020f,   0.81176f,   0.46667f },
  {   0.83529f,   0.76078f,   0.34902f },
  {   0.77255f,   0.72157f,   0.24706f },
  {   0.69412f,   0.68235f,   0.15294f },
  {   0.60784f,   0.65098f,   0.07843f },
  {   0.52157f,   0.62353f,   0.02745f },
  {   0.42353f,   0.58824f,   0.02745f },
  {   0.32941f,   0.55686f,   0.06667f },
  {   0.23137f,   0.51765f,   0.10980f },
  {   0.14510f,   0.47843f,   0.14118f },
  {   0.07451f,   0.43529f,   0.16078f },
  {   0.04314f,   0.38824f,   0.17255f },
  {   0.05882f,   0.33725f,   0.17255f },
  {   0.08235f,   0.28627f,   0.16471f },
  {   0.09804f,   0.23922f,   0.14118f },
  {   0.09804f,   0.18431f,   0.10980f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
