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
static const std::vector<vivid::srgb_t> Bilbao_7
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.80784f,   0.80000f,   0.76863f },
  {   0.72549f,   0.68627f,   0.54510f },
  {   0.66667f,   0.52549f,   0.39608f },
  {   0.61961f,   0.38039f,   0.33333f },
  {   0.49804f,   0.20000f,   0.19608f },
  {   0.30196f,   0.00000f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
