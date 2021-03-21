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
static const std::vector<vivid::srgb_t> Royal3_5
{
  {   0.98824f,   0.34118f,   0.42353f },
  {   0.92941f,   0.49412f,   0.32549f },
  {   0.88627f,   0.60000f,   0.54510f },
  {   0.18039f,   0.09020f,   0.09412f },
  {   0.98431f,   0.83922f,   0.79216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
