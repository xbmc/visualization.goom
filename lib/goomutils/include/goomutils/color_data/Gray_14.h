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
static const std::vector<vivid::srgb_t> Gray_14
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.05098f,   0.05098f,   0.05098f },
  {   0.12549f,   0.12549f,   0.12549f },
  {   0.20000f,   0.19608f,   0.19608f },
  {   0.26667f,   0.26275f,   0.26275f },
  {   0.33725f,   0.33333f,   0.33333f },
  {   0.40784f,   0.40784f,   0.40392f },
  {   0.47843f,   0.47843f,   0.47451f },
  {   0.55686f,   0.55294f,   0.55294f },
  {   0.63529f,   0.63529f,   0.63137f },
  {   0.71765f,   0.71373f,   0.70980f },
  {   0.80392f,   0.80392f,   0.80000f },
  {   0.89804f,   0.89412f,   0.89020f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
