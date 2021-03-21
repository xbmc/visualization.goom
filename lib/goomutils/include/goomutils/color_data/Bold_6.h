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
static const std::vector<vivid::srgb_t> Bold_6
{
  {   0.49804f,   0.23529f,   0.55294f },
  {   0.06667f,   0.64706f,   0.47451f },
  {   0.22353f,   0.41176f,   0.67451f },
  {   0.94902f,   0.71765f,   0.00392f },
  {   0.90588f,   0.24706f,   0.45490f },
  {   0.50196f,   0.72941f,   0.35294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
