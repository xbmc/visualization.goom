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
static const std::vector<vivid::srgb_t> BrBG_11
{
  {   0.32941f,   0.18824f,   0.01961f },
  {   0.54902f,   0.31765f,   0.03922f },
  {   0.74902f,   0.50588f,   0.17647f },
  {   0.87451f,   0.76078f,   0.49020f },
  {   0.96471f,   0.90980f,   0.76471f },
  {   0.96078f,   0.96078f,   0.96078f },
  {   0.78039f,   0.91765f,   0.89804f },
  {   0.50196f,   0.80392f,   0.75686f },
  {   0.20784f,   0.59216f,   0.56078f },
  {   0.00392f,   0.40000f,   0.36863f },
  {   0.00000f,   0.23529f,   0.18824f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
