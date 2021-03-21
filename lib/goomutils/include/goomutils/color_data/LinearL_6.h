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
static const std::vector<vivid::srgb_t> LinearL_6
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.15686f,   0.14902f,   0.47059f },
  {   0.00000f,   0.42353f,   0.39608f },
  {   0.07843f,   0.67059f,   0.00000f },
  {   0.81961f,   0.79608f,   0.34118f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
