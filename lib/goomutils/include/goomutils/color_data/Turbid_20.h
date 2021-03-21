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
static const std::vector<vivid::srgb_t> Turbid_20
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.88627f,   0.90588f,   0.59608f },
  {   0.85490f,   0.84314f,   0.51765f },
  {   0.83137f,   0.78431f,   0.45098f },
  {   0.80784f,   0.72157f,   0.38431f },
  {   0.78431f,   0.66667f,   0.33333f },
  {   0.75686f,   0.60784f,   0.29020f },
  {   0.72941f,   0.55686f,   0.25882f },
  {   0.69412f,   0.50980f,   0.24314f },
  {   0.65490f,   0.46275f,   0.23529f },
  {   0.61176f,   0.41961f,   0.23137f },
  {   0.56078f,   0.38039f,   0.22745f },
  {   0.50980f,   0.34510f,   0.22353f },
  {   0.45882f,   0.31373f,   0.21569f },
  {   0.40000f,   0.28235f,   0.20784f },
  {   0.34902f,   0.25098f,   0.19216f },
  {   0.29020f,   0.21961f,   0.17255f },
  {   0.23922f,   0.18824f,   0.15294f },
  {   0.18431f,   0.15294f,   0.12941f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
