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
static const std::vector<vivid::srgb_t> Oslo_9
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.05490f,   0.11765f,   0.18039f },
  {   0.08235f,   0.22353f,   0.35686f },
  {   0.14902f,   0.34118f,   0.54902f },
  {   0.31373f,   0.48235f,   0.73725f },
  {   0.48235f,   0.59608f,   0.79216f },
  {   0.63529f,   0.69020f,   0.79216f },
  {   0.80784f,   0.81961f,   0.84314f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
