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
static const std::vector<vivid::srgb_t> Haline_18
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.18039f,   0.11373f,   0.56863f },
  {   0.13333f,   0.18824f,   0.63922f },
  {   0.06667f,   0.27843f,   0.60392f },
  {   0.05098f,   0.34118f,   0.57255f },
  {   0.09412f,   0.39608f,   0.55294f },
  {   0.14118f,   0.44706f,   0.54118f },
  {   0.18431f,   0.49804f,   0.53725f },
  {   0.21961f,   0.54902f,   0.53333f },
  {   0.24706f,   0.60000f,   0.52549f },
  {   0.28235f,   0.65490f,   0.50980f },
  {   0.32941f,   0.70980f,   0.48235f },
  {   0.40000f,   0.76078f,   0.44314f },
  {   0.50196f,   0.80784f,   0.39216f },
  {   0.63922f,   0.84314f,   0.36078f },
  {   0.77647f,   0.87059f,   0.40000f },
  {   0.89020f,   0.90196f,   0.49412f },
  {   0.99216f,   0.93725f,   0.60392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
