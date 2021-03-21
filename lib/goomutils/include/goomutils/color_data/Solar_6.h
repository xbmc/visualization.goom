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
static const std::vector<vivid::srgb_t> Solar_6
{
  {   0.20000f,   0.07843f,   0.09412f },
  {   0.45098f,   0.15294f,   0.14118f },
  {   0.64706f,   0.29020f,   0.09020f },
  {   0.76863f,   0.49804f,   0.08235f },
  {   0.84706f,   0.72941f,   0.16471f },
  {   0.88235f,   0.99216f,   0.29412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
