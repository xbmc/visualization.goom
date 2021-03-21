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
static const std::vector<vivid::srgb_t> Hawaii_13
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.56863f,   0.13725f,   0.37255f },
  {   0.58039f,   0.21961f,   0.30196f },
  {   0.59216f,   0.30588f,   0.24314f },
  {   0.60000f,   0.38824f,   0.18824f },
  {   0.61176f,   0.47843f,   0.13333f },
  {   0.61176f,   0.58824f,   0.10980f },
  {   0.57255f,   0.69412f,   0.20784f },
  {   0.50196f,   0.77255f,   0.37255f },
  {   0.42353f,   0.83137f,   0.54902f },
  {   0.37255f,   0.88627f,   0.73333f },
  {   0.47843f,   0.93333f,   0.90588f },
  {   0.70196f,   0.94902f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
