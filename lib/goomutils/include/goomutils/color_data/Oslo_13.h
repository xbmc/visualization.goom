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
static const std::vector<vivid::srgb_t> Oslo_13
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.04706f,   0.08627f,   0.12549f },
  {   0.06275f,   0.14902f,   0.23529f },
  {   0.08235f,   0.22353f,   0.35686f },
  {   0.12157f,   0.29804f,   0.48235f },
  {   0.18824f,   0.38039f,   0.61176f },
  {   0.31373f,   0.48235f,   0.73725f },
  {   0.43529f,   0.56471f,   0.78824f },
  {   0.53725f,   0.62745f,   0.79216f },
  {   0.63529f,   0.69020f,   0.79216f },
  {   0.74118f,   0.76863f,   0.81176f },
  {   0.87059f,   0.87843f,   0.88627f },
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
