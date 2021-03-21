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
static const std::vector<vivid::srgb_t> RedOr_6
{
  {   0.96471f,   0.82353f,   0.66275f },
  {   0.96078f,   0.71765f,   0.55686f },
  {   0.94510f,   0.61176f,   0.48627f },
  {   0.86667f,   0.40784f,   0.42353f },
  {   0.79216f,   0.32157f,   0.40784f },
  {   0.69412f,   0.24706f,   0.39216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
