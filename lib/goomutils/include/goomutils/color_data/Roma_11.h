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
static const std::vector<vivid::srgb_t> Roma_11
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.60784f,   0.33333f,   0.08627f },
  {   0.70196f,   0.52549f,   0.17255f },
  {   0.81176f,   0.74118f,   0.32941f },
  {   0.89020f,   0.89804f,   0.60392f },
  {   0.79216f,   0.92157f,   0.78824f },
  {   0.54118f,   0.84706f,   0.84706f },
  {   0.33333f,   0.68627f,   0.80784f },
  {   0.24314f,   0.50980f,   0.73333f },
  {   0.17647f,   0.34902f,   0.66275f },
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
