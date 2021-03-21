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
static const std::vector<vivid::srgb_t> Phase_6
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.86275f,   0.23529f,   0.42745f },
  {   0.71373f,   0.29412f,   0.92941f },
  {   0.23137f,   0.54902f,   0.79608f },
  {   0.09804f,   0.60392f,   0.36863f },
  {   0.65882f,   0.47059f,   0.05098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
