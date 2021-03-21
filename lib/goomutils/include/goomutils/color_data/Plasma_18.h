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
static const std::vector<vivid::srgb_t> Plasma_18
{
  {   0.05098f,   0.03137f,   0.52941f },
  {   0.18431f,   0.01961f,   0.58824f },
  {   0.28627f,   0.01176f,   0.62745f },
  {   0.38039f,   0.00000f,   0.65490f },
  {   0.47059f,   0.00392f,   0.65882f },
  {   0.55686f,   0.04706f,   0.64314f },
  {   0.63529f,   0.11373f,   0.60392f },
  {   0.70588f,   0.18039f,   0.55294f },
  {   0.76863f,   0.24314f,   0.49804f },
  {   0.82353f,   0.30980f,   0.44314f },
  {   0.87059f,   0.38039f,   0.39216f },
  {   0.91373f,   0.44706f,   0.34118f },
  {   0.95294f,   0.52157f,   0.29412f },
  {   0.97647f,   0.60392f,   0.24314f },
  {   0.99216f,   0.68627f,   0.19216f },
  {   0.99216f,   0.77647f,   0.15294f },
  {   0.97255f,   0.87451f,   0.14510f },
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
