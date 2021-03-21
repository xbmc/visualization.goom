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
static const std::vector<vivid::srgb_t> Lisbon_18
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.74118f,   0.78431f,   0.90588f },
  {   0.58824f,   0.67059f,   0.81176f },
  {   0.43529f,   0.55686f,   0.72157f },
  {   0.29020f,   0.44706f,   0.61961f },
  {   0.16863f,   0.33333f,   0.49804f },
  {   0.09804f,   0.23529f,   0.36471f },
  {   0.07059f,   0.15294f,   0.23529f },
  {   0.07059f,   0.09804f,   0.12941f },
  {   0.11765f,   0.11373f,   0.09020f },
  {   0.20000f,   0.18824f,   0.12549f },
  {   0.30196f,   0.28627f,   0.18039f },
  {   0.41176f,   0.38824f,   0.24706f },
  {   0.52941f,   0.49804f,   0.32157f },
  {   0.65098f,   0.61961f,   0.41569f },
  {   0.77255f,   0.74510f,   0.54510f },
  {   0.88627f,   0.87059f,   0.69412f },
  {   1.00000f,   1.00000f,   0.85098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
