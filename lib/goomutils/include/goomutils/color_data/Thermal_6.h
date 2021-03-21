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
static const std::vector<vivid::srgb_t> Thermal_6
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.25098f,   0.20392f,   0.62353f },
  {   0.54510f,   0.32549f,   0.55294f },
  {   0.83922f,   0.42353f,   0.42353f },
  {   0.98824f,   0.65098f,   0.23529f },
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
