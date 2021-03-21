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
static const std::vector<vivid::srgb_t> Pastel2_4
{
  {   0.70196f,   0.88627f,   0.80392f },
  {   0.99216f,   0.80392f,   0.67451f },
  {   0.79608f,   0.83529f,   0.90980f },
  {   0.95686f,   0.79216f,   0.89412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
