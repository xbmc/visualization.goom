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
static const std::vector<vivid::srgb_t> Solar_7
{
  {   0.20000f,   0.07843f,   0.09412f },
  {   0.40784f,   0.13725f,   0.14510f },
  {   0.59216f,   0.23137f,   0.10980f },
  {   0.71373f,   0.39216f,   0.07451f },
  {   0.79608f,   0.57255f,   0.10196f },
  {   0.85490f,   0.76863f,   0.18431f },
  {   0.88235f,   0.99216f,   0.29412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
