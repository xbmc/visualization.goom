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
static const std::vector<vivid::srgb_t> Aquatic3_5
{
  {   0.83922f,   0.63137f,   0.25882f },
  {   0.76078f,   0.50196f,   0.44706f },
  {   0.78431f,   0.71765f,   0.63137f },
  {   0.74118f,   0.26667f,   0.17647f },
  {   0.39216f,   0.32941f,   0.23529f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
