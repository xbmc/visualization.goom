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
static const std::vector<vivid::srgb_t> Berlin_16
{
  {   0.61961f,   0.69020f,   1.00000f },
  {   0.46275f,   0.67059f,   0.92549f },
  {   0.30196f,   0.61569f,   0.81176f },
  {   0.19608f,   0.50196f,   0.65098f },
  {   0.14510f,   0.37647f,   0.48627f },
  {   0.10196f,   0.25882f,   0.33725f },
  {   0.06667f,   0.15294f,   0.19608f },
  {   0.07059f,   0.07059f,   0.08235f },
  {   0.13333f,   0.04706f,   0.00784f },
  {   0.21569f,   0.06275f,   0.00000f },
  {   0.31373f,   0.09412f,   0.01176f },
  {   0.45098f,   0.16863f,   0.08627f },
  {   0.58824f,   0.29020f,   0.21176f },
  {   0.72157f,   0.41569f,   0.36078f },
  {   0.85882f,   0.54510f,   0.51765f },
  {   1.00000f,   0.67843f,   0.67843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
