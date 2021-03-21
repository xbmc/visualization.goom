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
static const std::vector<vivid::srgb_t> Tofino_19
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.72157f,   0.74510f,   0.93725f },
  {   0.57647f,   0.64314f,   0.87059f },
  {   0.43137f,   0.53725f,   0.79608f },
  {   0.29020f,   0.41961f,   0.67451f },
  {   0.20784f,   0.32157f,   0.53333f },
  {   0.15294f,   0.23529f,   0.39608f },
  {   0.10588f,   0.16078f,   0.26275f },
  {   0.07059f,   0.09804f,   0.14902f },
  {   0.05098f,   0.08627f,   0.07451f },
  {   0.07059f,   0.13333f,   0.07843f },
  {   0.10196f,   0.21176f,   0.10980f },
  {   0.14118f,   0.30196f,   0.15686f },
  {   0.18824f,   0.40000f,   0.20784f },
  {   0.24706f,   0.50588f,   0.26667f },
  {   0.36078f,   0.61961f,   0.34118f },
  {   0.53333f,   0.72549f,   0.43922f },
  {   0.69804f,   0.81569f,   0.52549f },
  {   0.85882f,   0.90196f,   0.60784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
