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
static const std::vector<vivid::srgb_t> Bamako_7
{
  {   0.00000f,   0.25098f,   0.29804f },
  {   0.10980f,   0.31765f,   0.23922f },
  {   0.22745f,   0.39608f,   0.16471f },
  {   0.38039f,   0.49412f,   0.07843f },
  {   0.58824f,   0.57255f,   0.02353f },
  {   0.84706f,   0.74510f,   0.30196f },
  {   1.00000f,   0.89804f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
