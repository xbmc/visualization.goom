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
static const std::vector<vivid::srgb_t> Tofino_5
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.24314f,   0.36863f,   0.60392f },
  {   0.05098f,   0.08627f,   0.07451f },
  {   0.21569f,   0.45098f,   0.23529f },
  {   0.85882f,   0.90196f,   0.60784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
