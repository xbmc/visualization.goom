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
static const std::vector<vivid::srgb_t> Dark2_4
{
  {   0.10588f,   0.61961f,   0.46667f },
  {   0.85098f,   0.37255f,   0.00784f },
  {   0.45882f,   0.43922f,   0.70196f },
  {   0.90588f,   0.16078f,   0.54118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
