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
static const std::vector<vivid::srgb_t> Darjeeling1_4
{
  {   0.61961f,   0.59216f,   0.59216f },
  {   0.76078f,   0.55686f,   0.00000f },
  {   0.51373f,   0.40000f,   0.34902f },
  {   0.61176f,   0.35294f,   0.20000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
