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
static const std::vector<vivid::srgb_t> Berlin_10
{
  {   0.61961f,   0.69020f,   1.00000f },
  {   0.35686f,   0.64314f,   0.85882f },
  {   0.17647f,   0.45882f,   0.59216f },
  {   0.10196f,   0.25882f,   0.33725f },
  {   0.06667f,   0.09804f,   0.11765f },
  {   0.15686f,   0.05098f,   0.00392f },
  {   0.31373f,   0.09412f,   0.01176f },
  {   0.54118f,   0.24706f,   0.16471f },
  {   0.76863f,   0.45882f,   0.41569f },
  {   1.00000f,   0.67843f,   0.67843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
