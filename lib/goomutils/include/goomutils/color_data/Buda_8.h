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
static const std::vector<vivid::srgb_t> Buda_8
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.70588f,   0.20000f,   0.60392f },
  {   0.74510f,   0.33725f,   0.55294f },
  {   0.78824f,   0.45882f,   0.51373f },
  {   0.81961f,   0.58431f,   0.47843f },
  {   0.85098f,   0.70980f,   0.44706f },
  {   0.88627f,   0.84314f,   0.41569f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
