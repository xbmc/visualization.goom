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
static const std::vector<vivid::srgb_t> PuRd_4
{
  {   0.94510f,   0.93333f,   0.96471f },
  {   0.84314f,   0.70980f,   0.84706f },
  {   0.87451f,   0.39608f,   0.69020f },
  {   0.80784f,   0.07059f,   0.33725f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
