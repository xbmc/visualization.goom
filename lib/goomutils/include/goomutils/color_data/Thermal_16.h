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
static const std::vector<vivid::srgb_t> Thermal_16
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.03529f,   0.18039f,   0.33725f },
  {   0.10980f,   0.20392f,   0.50980f },
  {   0.25098f,   0.20392f,   0.62353f },
  {   0.36078f,   0.24314f,   0.60392f },
  {   0.45490f,   0.28627f,   0.57255f },
  {   0.54510f,   0.32549f,   0.55294f },
  {   0.63922f,   0.35686f,   0.52549f },
  {   0.74118f,   0.38824f,   0.48627f },
  {   0.83922f,   0.42353f,   0.42353f },
  {   0.92157f,   0.47451f,   0.34510f },
  {   0.96863f,   0.54902f,   0.27059f },
  {   0.98824f,   0.65098f,   0.23529f },
  {   0.98039f,   0.75686f,   0.25098f },
  {   0.95294f,   0.86667f,   0.29412f },
  {   0.90980f,   0.98039f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
