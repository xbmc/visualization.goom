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
static const std::vector<vivid::srgb_t> Thermal_19
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.02745f,   0.17255f,   0.31373f },
  {   0.07451f,   0.20000f,   0.44706f },
  {   0.17255f,   0.20000f,   0.58431f },
  {   0.29412f,   0.21569f,   0.62353f },
  {   0.37647f,   0.25098f,   0.60000f },
  {   0.45490f,   0.28627f,   0.57255f },
  {   0.52941f,   0.31765f,   0.55686f },
  {   0.60392f,   0.34510f,   0.53725f },
  {   0.69412f,   0.37255f,   0.50980f },
  {   0.77647f,   0.40000f,   0.46667f },
  {   0.85490f,   0.43137f,   0.41176f },
  {   0.92157f,   0.47451f,   0.34510f },
  {   0.96471f,   0.53333f,   0.28235f },
  {   0.98431f,   0.61176f,   0.24314f },
  {   0.98431f,   0.69804f,   0.23922f },
  {   0.97255f,   0.79608f,   0.26275f },
  {   0.94902f,   0.88627f,   0.30588f },
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
