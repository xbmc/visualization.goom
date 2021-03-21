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
static const std::vector<vivid::srgb_t> Viridis_6
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.25490f,   0.26667f,   0.52941f },
  {   0.16471f,   0.47059f,   0.55686f },
  {   0.13333f,   0.65882f,   0.51765f },
  {   0.47843f,   0.81961f,   0.31765f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
