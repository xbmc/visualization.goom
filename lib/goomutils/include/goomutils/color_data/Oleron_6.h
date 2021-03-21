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
static const std::vector<vivid::srgb_t> Oleron_6
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.42353f,   0.47451f,   0.67451f },
  {   0.76863f,   0.81961f,   0.96471f },
  {   0.32549f,   0.36863f,   0.00784f },
  {   0.77255f,   0.64314f,   0.42353f },
  {   0.99216f,   0.99216f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
