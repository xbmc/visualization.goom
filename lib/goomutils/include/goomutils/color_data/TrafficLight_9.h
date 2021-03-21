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
static const std::vector<vivid::srgb_t> TrafficLight_9
{
  {   0.69412f,   0.01176f,   0.09412f },
  {   0.85882f,   0.63137f,   0.22745f },
  {   0.18824f,   0.57647f,   0.26275f },
  {   0.84706f,   0.14510f,   0.14902f },
  {   1.00000f,   0.75686f,   0.33725f },
  {   0.41176f,   0.71765f,   0.39216f },
  {   0.94902f,   0.42353f,   0.39216f },
  {   1.00000f,   0.86667f,   0.44314f },
  {   0.62353f,   0.80392f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
