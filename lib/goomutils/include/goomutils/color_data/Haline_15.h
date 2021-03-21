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
static const std::vector<vivid::srgb_t> Haline_15
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.18039f,   0.11765f,   0.59608f },
  {   0.10588f,   0.22745f,   0.62745f },
  {   0.04706f,   0.32157f,   0.58039f },
  {   0.08627f,   0.38824f,   0.55294f },
  {   0.14510f,   0.45098f,   0.54118f },
  {   0.19216f,   0.50980f,   0.53333f },
  {   0.23529f,   0.57647f,   0.52941f },
  {   0.27451f,   0.64314f,   0.51373f },
  {   0.32549f,   0.70588f,   0.48627f },
  {   0.41176f,   0.76863f,   0.43529f },
  {   0.54510f,   0.81961f,   0.37647f },
  {   0.72157f,   0.85882f,   0.37647f },
  {   0.87059f,   0.89412f,   0.47451f },
  {   0.99216f,   0.93725f,   0.60392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
