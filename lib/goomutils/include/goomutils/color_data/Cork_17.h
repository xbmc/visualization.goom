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
static const std::vector<vivid::srgb_t> Cork_17
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.19216f,   0.38824f },
  {   0.16471f,   0.28627f,   0.48235f },
  {   0.22353f,   0.38824f,   0.57255f },
  {   0.34118f,   0.49412f,   0.65098f },
  {   0.47451f,   0.60000f,   0.72549f },
  {   0.61569f,   0.70588f,   0.79608f },
  {   0.75686f,   0.81569f,   0.87059f },
  {   0.85882f,   0.90196f,   0.89804f },
  {   0.79608f,   0.87843f,   0.80784f },
  {   0.67059f,   0.80784f,   0.68235f },
  {   0.54510f,   0.73333f,   0.56078f },
  {   0.41961f,   0.65882f,   0.43922f },
  {   0.30588f,   0.56863f,   0.30588f },
  {   0.25490f,   0.46275f,   0.18039f },
  {   0.25490f,   0.37647f,   0.09020f },
  {   0.25882f,   0.30196f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
