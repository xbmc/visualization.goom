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
static const std::vector<vivid::srgb_t> PuRd_6
{
  {   0.94510f,   0.93333f,   0.96471f },
  {   0.83137f,   0.72549f,   0.85490f },
  {   0.78824f,   0.58039f,   0.78039f },
  {   0.87451f,   0.39608f,   0.69020f },
  {   0.86667f,   0.10980f,   0.46667f },
  {   0.59608f,   0.00000f,   0.26275f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
