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
static const std::vector<vivid::srgb_t> Oslo_16
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.04314f,   0.07451f,   0.10980f },
  {   0.05490f,   0.12157f,   0.19216f },
  {   0.07059f,   0.17647f,   0.28235f },
  {   0.09020f,   0.23529f,   0.38039f },
  {   0.12157f,   0.29804f,   0.48235f },
  {   0.17255f,   0.36471f,   0.58824f },
  {   0.25490f,   0.43922f,   0.69412f },
  {   0.36078f,   0.51765f,   0.76471f },
  {   0.45490f,   0.58039f,   0.78824f },
  {   0.53725f,   0.62745f,   0.79216f },
  {   0.61569f,   0.67843f,   0.78824f },
  {   0.69804f,   0.73725f,   0.80000f },
  {   0.79216f,   0.80784f,   0.83529f },
  {   0.89804f,   0.90196f,   0.90588f },
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
