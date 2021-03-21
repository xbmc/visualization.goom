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
static const std::vector<vivid::srgb_t> PRGn_5
{
  {   0.48235f,   0.19608f,   0.58039f },
  {   0.76078f,   0.64706f,   0.81176f },
  {   0.96863f,   0.96863f,   0.96863f },
  {   0.65098f,   0.85882f,   0.62745f },
  {   0.00000f,   0.53333f,   0.21569f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
