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
static const std::vector<vivid::srgb_t> Speed_12
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.93725f,   0.88627f,   0.61176f },
  {   0.86667f,   0.79216f,   0.41569f },
  {   0.75686f,   0.71373f,   0.22353f },
  {   0.61569f,   0.65490f,   0.08235f },
  {   0.45882f,   0.60000f,   0.02353f },
  {   0.29412f,   0.54118f,   0.08235f },
  {   0.14118f,   0.47451f,   0.14118f },
  {   0.04314f,   0.39608f,   0.17255f },
  {   0.07059f,   0.30980f,   0.16863f },
  {   0.09804f,   0.22353f,   0.13333f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
