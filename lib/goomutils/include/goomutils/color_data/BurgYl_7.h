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
static const std::vector<vivid::srgb_t> BurgYl_7
{
  {   0.98431f,   0.90196f,   0.77255f },
  {   0.96078f,   0.72941f,   0.59608f },
  {   0.93333f,   0.54118f,   0.50980f },
  {   0.86275f,   0.44314f,   0.46275f },
  {   0.78431f,   0.34510f,   0.42353f },
  {   0.61176f,   0.24706f,   0.36471f },
  {   0.43922f,   0.15686f,   0.29020f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
