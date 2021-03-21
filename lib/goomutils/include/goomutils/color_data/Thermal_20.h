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
static const std::vector<vivid::srgb_t> Thermal_20
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.02745f,   0.17255f,   0.30196f },
  {   0.07059f,   0.19608f,   0.43529f },
  {   0.15294f,   0.20392f,   0.56863f },
  {   0.27451f,   0.20784f,   0.62745f },
  {   0.35686f,   0.23922f,   0.60784f },
  {   0.43137f,   0.27843f,   0.58039f },
  {   0.50196f,   0.30588f,   0.56078f },
  {   0.57255f,   0.33333f,   0.54510f },
  {   0.65098f,   0.36078f,   0.52549f },
  {   0.72941f,   0.38431f,   0.49412f },
  {   0.80784f,   0.41176f,   0.44314f },
  {   0.87843f,   0.44314f,   0.38824f },
  {   0.93333f,   0.49020f,   0.32549f },
  {   0.97255f,   0.55686f,   0.26667f },
  {   0.98431f,   0.63137f,   0.23922f },
  {   0.98431f,   0.71765f,   0.23922f },
  {   0.97255f,   0.80392f,   0.26667f },
  {   0.94510f,   0.89412f,   0.30980f },
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
