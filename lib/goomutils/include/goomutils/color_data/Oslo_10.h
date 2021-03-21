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
static const std::vector<vivid::srgb_t> Oslo_10
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.05098f,   0.10588f,   0.16078f },
  {   0.07451f,   0.19608f,   0.31765f },
  {   0.12157f,   0.29804f,   0.48235f },
  {   0.21961f,   0.41176f,   0.65882f },
  {   0.39608f,   0.54118f,   0.78039f },
  {   0.53725f,   0.62745f,   0.79216f },
  {   0.66667f,   0.71373f,   0.79216f },
  {   0.83137f,   0.83922f,   0.85882f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
