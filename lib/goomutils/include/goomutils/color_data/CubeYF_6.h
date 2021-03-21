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
static const std::vector<vivid::srgb_t> CubeYF_6
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.45098f,   0.34118f,   0.97255f },
  {   0.29804f,   0.61961f,   0.85098f },
  {   0.27843f,   0.80392f,   0.52157f },
  {   0.46275f,   0.91373f,   0.30196f },
  {   0.81961f,   0.92157f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
