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
static const std::vector<vivid::srgb_t> SunsetDark_5
{
  {   0.98824f,   0.87059f,   0.61176f },
  {   0.94118f,   0.45490f,   0.43137f },
  {   0.89020f,   0.30980f,   0.43529f },
  {   0.86275f,   0.22353f,   0.46667f },
  {   0.48627f,   0.11373f,   0.43529f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
