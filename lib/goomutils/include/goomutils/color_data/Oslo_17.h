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
static const std::vector<vivid::srgb_t> Oslo_17
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.03922f,   0.07059f,   0.10588f },
  {   0.05490f,   0.11765f,   0.18039f },
  {   0.06667f,   0.16863f,   0.26667f },
  {   0.08235f,   0.22353f,   0.35686f },
  {   0.10980f,   0.28235f,   0.45098f },
  {   0.14902f,   0.34118f,   0.54902f },
  {   0.21569f,   0.40392f,   0.65098f },
  {   0.31373f,   0.48235f,   0.73725f },
  {   0.40392f,   0.54510f,   0.78039f },
  {   0.48235f,   0.59608f,   0.79216f },
  {   0.55686f,   0.64314f,   0.78824f },
  {   0.63529f,   0.69020f,   0.79216f },
  {   0.71373f,   0.74510f,   0.80392f },
  {   0.80784f,   0.81961f,   0.84314f },
  {   0.90196f,   0.90588f,   0.91373f },
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
