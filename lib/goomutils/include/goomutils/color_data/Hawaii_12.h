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
static const std::vector<vivid::srgb_t> Hawaii_12
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.56863f,   0.14510f,   0.36471f },
  {   0.58039f,   0.23529f,   0.29020f },
  {   0.59216f,   0.32549f,   0.22745f },
  {   0.60392f,   0.41961f,   0.16471f },
  {   0.61569f,   0.52941f,   0.11373f },
  {   0.59608f,   0.64706f,   0.14902f },
  {   0.52941f,   0.74510f,   0.30588f },
  {   0.44314f,   0.81569f,   0.49804f },
  {   0.37647f,   0.87843f,   0.70588f },
  {   0.46275f,   0.92941f,   0.89020f },
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
