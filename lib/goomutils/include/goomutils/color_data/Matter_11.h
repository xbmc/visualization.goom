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
static const std::vector<vivid::srgb_t> Matter_11
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98039f,   0.78824f,   0.55686f },
  {   0.96078f,   0.65490f,   0.45098f },
  {   0.93333f,   0.52157f,   0.36863f },
  {   0.88627f,   0.38431f,   0.32549f },
  {   0.80784f,   0.26275f,   0.33725f },
  {   0.70196f,   0.18039f,   0.37255f },
  {   0.58431f,   0.12549f,   0.38824f },
  {   0.44706f,   0.10196f,   0.37647f },
  {   0.30980f,   0.08627f,   0.32157f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
