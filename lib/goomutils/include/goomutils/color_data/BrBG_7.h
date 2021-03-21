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
static const std::vector<vivid::srgb_t> BrBG_7
{
  {   0.54902f,   0.31765f,   0.03922f },
  {   0.84706f,   0.70196f,   0.39608f },
  {   0.96471f,   0.90980f,   0.76471f },
  {   0.96078f,   0.96078f,   0.96078f },
  {   0.78039f,   0.91765f,   0.89804f },
  {   0.35294f,   0.70588f,   0.67451f },
  {   0.00392f,   0.40000f,   0.36863f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
