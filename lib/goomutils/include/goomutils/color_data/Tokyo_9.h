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
static const std::vector<vivid::srgb_t> Tokyo_9
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.29412f,   0.13725f,   0.31373f },
  {   0.46275f,   0.27451f,   0.42353f },
  {   0.53725f,   0.41176f,   0.49020f },
  {   0.56471f,   0.52941f,   0.52549f },
  {   0.58431f,   0.64314f,   0.55686f },
  {   0.63137f,   0.77255f,   0.60000f },
  {   0.80784f,   0.93333f,   0.71765f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
