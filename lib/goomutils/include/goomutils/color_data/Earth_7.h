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
static const std::vector<vivid::srgb_t> Earth_7
{
  {   0.63137f,   0.41176f,   0.15686f },
  {   0.74118f,   0.57255f,   0.35294f },
  {   0.83922f,   0.74118f,   0.55294f },
  {   0.92941f,   0.91765f,   0.76078f },
  {   0.70980f,   0.78431f,   0.72157f },
  {   0.47451f,   0.65490f,   0.67451f },
  {   0.15686f,   0.52941f,   0.63137f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
