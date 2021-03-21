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
static const std::vector<vivid::srgb_t> Amp_8
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.88235f,   0.76471f,   0.72549f },
  {   0.83137f,   0.59608f,   0.51765f },
  {   0.78039f,   0.43529f,   0.32157f },
  {   0.71765f,   0.25490f,   0.16471f },
  {   0.60392f,   0.08627f,   0.15294f },
  {   0.41961f,   0.05882f,   0.14510f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
