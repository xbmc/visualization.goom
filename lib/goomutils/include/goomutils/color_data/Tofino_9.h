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
static const std::vector<vivid::srgb_t> Tofino_9
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.53333f,   0.61569f,   0.85098f },
  {   0.24314f,   0.36863f,   0.60392f },
  {   0.11373f,   0.17647f,   0.29020f },
  {   0.05098f,   0.08627f,   0.07451f },
  {   0.10980f,   0.23137f,   0.12157f },
  {   0.21569f,   0.45098f,   0.23529f },
  {   0.48627f,   0.70196f,   0.41176f },
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
