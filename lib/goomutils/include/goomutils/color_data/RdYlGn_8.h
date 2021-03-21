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
static const std::vector<vivid::srgb_t> RdYlGn_8
{
  {   0.84314f,   0.18824f,   0.15294f },
  {   0.95686f,   0.42745f,   0.26275f },
  {   0.99216f,   0.68235f,   0.38039f },
  {   0.99608f,   0.87843f,   0.54510f },
  {   0.85098f,   0.93725f,   0.54510f },
  {   0.65098f,   0.85098f,   0.41569f },
  {   0.40000f,   0.74118f,   0.38824f },
  {   0.10196f,   0.59608f,   0.31373f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
