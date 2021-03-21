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
static const std::vector<vivid::srgb_t> RdYlGn_6
{
  {   0.84314f,   0.18824f,   0.15294f },
  {   0.98824f,   0.55294f,   0.34902f },
  {   0.99608f,   0.87843f,   0.54510f },
  {   0.85098f,   0.93725f,   0.54510f },
  {   0.56863f,   0.81176f,   0.37647f },
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
