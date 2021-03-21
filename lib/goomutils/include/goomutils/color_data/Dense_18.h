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
static const std::vector<vivid::srgb_t> Dense_18
{
  {   0.90196f,   0.94510f,   0.94510f },
  {   0.80000f,   0.89412f,   0.90980f },
  {   0.70588f,   0.84706f,   0.89412f },
  {   0.61961f,   0.79608f,   0.88627f },
  {   0.54118f,   0.74118f,   0.89020f },
  {   0.48627f,   0.68235f,   0.89412f },
  {   0.45882f,   0.61961f,   0.89804f },
  {   0.45490f,   0.55294f,   0.88627f },
  {   0.46275f,   0.48235f,   0.85882f },
  {   0.47451f,   0.41176f,   0.81176f },
  {   0.47451f,   0.34510f,   0.74902f },
  {   0.46667f,   0.28235f,   0.67059f },
  {   0.45098f,   0.22353f,   0.58824f },
  {   0.42745f,   0.16863f,   0.49804f },
  {   0.39216f,   0.12157f,   0.40392f },
  {   0.34510f,   0.09020f,   0.30588f },
  {   0.28235f,   0.07059f,   0.21569f },
  {   0.21176f,   0.05490f,   0.14118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
