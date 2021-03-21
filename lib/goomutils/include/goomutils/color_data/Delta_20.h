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
static const std::vector<vivid::srgb_t> Delta_20
{
  {   0.06667f,   0.12549f,   0.25098f },
  {   0.12941f,   0.19216f,   0.42745f },
  {   0.12941f,   0.27451f,   0.60392f },
  {   0.10588f,   0.38824f,   0.62353f },
  {   0.14902f,   0.49412f,   0.64706f },
  {   0.21961f,   0.58824f,   0.67059f },
  {   0.35686f,   0.68235f,   0.69412f },
  {   0.56078f,   0.76078f,   0.73333f },
  {   0.74510f,   0.84314f,   0.80392f },
  {   0.91373f,   0.93333f,   0.87843f },
  {   0.96471f,   0.92941f,   0.69412f },
  {   0.89020f,   0.81176f,   0.46667f },
  {   0.77255f,   0.72157f,   0.24706f },
  {   0.60784f,   0.65098f,   0.07843f },
  {   0.42353f,   0.58824f,   0.02745f },
  {   0.23922f,   0.52157f,   0.10588f },
  {   0.07451f,   0.43529f,   0.16078f },
  {   0.05882f,   0.33725f,   0.17255f },
  {   0.09804f,   0.23922f,   0.14118f },
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
