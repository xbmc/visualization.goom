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
static const std::vector<vivid::srgb_t> Ice_18
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.07059f,   0.07451f,   0.15686f },
  {   0.12157f,   0.12157f,   0.24314f },
  {   0.17255f,   0.16471f,   0.33333f },
  {   0.21176f,   0.20784f,   0.43137f },
  {   0.23922f,   0.25882f,   0.52941f },
  {   0.24706f,   0.31765f,   0.61569f },
  {   0.24314f,   0.38039f,   0.67059f },
  {   0.25098f,   0.44706f,   0.70588f },
  {   0.27451f,   0.50980f,   0.72941f },
  {   0.31373f,   0.57255f,   0.75294f },
  {   0.36471f,   0.63529f,   0.77255f },
  {   0.42353f,   0.69804f,   0.79608f },
  {   0.49804f,   0.76078f,   0.82353f },
  {   0.59216f,   0.81961f,   0.85098f },
  {   0.70196f,   0.87451f,   0.89020f },
  {   0.81176f,   0.92941f,   0.93725f },
  {   0.91765f,   0.99216f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
