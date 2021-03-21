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
static const std::vector<vivid::srgb_t> Thermal_9
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.09804f,   0.20000f,   0.48627f },
  {   0.33725f,   0.23137f,   0.61176f },
  {   0.51373f,   0.31373f,   0.56078f },
  {   0.69412f,   0.37255f,   0.50980f },
  {   0.87059f,   0.43922f,   0.39608f },
  {   0.97647f,   0.57255f,   0.25882f },
  {   0.97647f,   0.76863f,   0.25490f },
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
