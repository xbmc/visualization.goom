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
static const std::vector<vivid::srgb_t> Tofino_6
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.34118f,   0.46667f,   0.72941f },
  {   0.09804f,   0.14510f,   0.23922f },
  {   0.09412f,   0.19608f,   0.10196f },
  {   0.29020f,   0.55294f,   0.29412f },
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
