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
static const std::vector<vivid::srgb_t> Roma_6
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.70196f,   0.52549f,   0.17255f },
  {   0.89020f,   0.89804f,   0.60392f },
  {   0.54118f,   0.84706f,   0.84706f },
  {   0.24314f,   0.50980f,   0.73333f },
  {   0.10196f,   0.20000f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
