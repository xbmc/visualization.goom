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
static const std::vector<vivid::srgb_t> Deep_12
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.80784f,   0.92549f,   0.70196f },
  {   0.61176f,   0.86275f,   0.64706f },
  {   0.43137f,   0.78431f,   0.63922f },
  {   0.34118f,   0.69412f,   0.64314f },
  {   0.29804f,   0.60392f,   0.62745f },
  {   0.26667f,   0.51373f,   0.60784f },
  {   0.24706f,   0.42353f,   0.58824f },
  {   0.24706f,   0.32941f,   0.56471f },
  {   0.25098f,   0.23529f,   0.45098f },
  {   0.21176f,   0.16863f,   0.30196f },
  {   0.15686f,   0.10196f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
