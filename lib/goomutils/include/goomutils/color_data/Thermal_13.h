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
static const std::vector<vivid::srgb_t> Thermal_13
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.04706f,   0.18824f,   0.37647f },
  {   0.17255f,   0.20000f,   0.58431f },
  {   0.33725f,   0.23137f,   0.61176f },
  {   0.45490f,   0.28627f,   0.57255f },
  {   0.56471f,   0.33333f,   0.54510f },
  {   0.69412f,   0.37255f,   0.50980f },
  {   0.81569f,   0.41176f,   0.43922f },
  {   0.92157f,   0.47451f,   0.34510f },
  {   0.97647f,   0.57255f,   0.25882f },
  {   0.98431f,   0.69804f,   0.23922f },
  {   0.96078f,   0.84314f,   0.28235f },
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
