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
static const std::vector<vivid::srgb_t> BrBG_5
{
  {   0.65098f,   0.38039f,   0.10196f },
  {   0.87451f,   0.76078f,   0.49020f },
  {   0.96078f,   0.96078f,   0.96078f },
  {   0.50196f,   0.80392f,   0.75686f },
  {   0.00392f,   0.52157f,   0.44314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
