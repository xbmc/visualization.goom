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
static const std::vector<vivid::srgb_t> Davos_18
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.02745f,   0.10588f,   0.37647f },
  {   0.07451f,   0.18431f,   0.45490f },
  {   0.11765f,   0.26275f,   0.52549f },
  {   0.16863f,   0.33725f,   0.57647f },
  {   0.22745f,   0.40000f,   0.60784f },
  {   0.28235f,   0.45490f,   0.61569f },
  {   0.33725f,   0.49804f,   0.60784f },
  {   0.39608f,   0.53725f,   0.58824f },
  {   0.45098f,   0.57255f,   0.56471f },
  {   0.50588f,   0.61176f,   0.54118f },
  {   0.57255f,   0.65882f,   0.52941f },
  {   0.65882f,   0.72157f,   0.54510f },
  {   0.76471f,   0.80392f,   0.60000f },
  {   0.87059f,   0.89020f,   0.70196f },
  {   0.94510f,   0.94902f,   0.81176f },
  {   0.98039f,   0.98039f,   0.90980f },
  {   0.99608f,   0.99608f,   0.99608f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
