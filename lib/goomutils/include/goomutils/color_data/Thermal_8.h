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
static const std::vector<vivid::srgb_t> Thermal_8
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.12157f,   0.20392f,   0.52941f },
  {   0.38824f,   0.25490f,   0.59608f },
  {   0.58431f,   0.33725f,   0.54118f },
  {   0.80000f,   0.40784f,   0.45098f },
  {   0.96078f,   0.52549f,   0.29020f },
  {   0.98039f,   0.74510f,   0.24706f },
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
