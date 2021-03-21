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
static const std::vector<vivid::srgb_t> GrayC_12
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.89804f,   0.89804f,   0.89804f },
  {   0.80000f,   0.80000f,   0.80000f },
  {   0.69804f,   0.69804f,   0.69804f },
  {   0.60392f,   0.60392f,   0.60392f },
  {   0.50980f,   0.50980f,   0.50980f },
  {   0.42353f,   0.42353f,   0.42353f },
  {   0.33725f,   0.33725f,   0.33725f },
  {   0.25490f,   0.25490f,   0.25490f },
  {   0.17255f,   0.17255f,   0.17255f },
  {   0.10196f,   0.10196f,   0.10196f },
  {   0.00000f,   0.00000f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
