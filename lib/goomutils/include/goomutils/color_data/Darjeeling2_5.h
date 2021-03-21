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
static const std::vector<vivid::srgb_t> Darjeeling2_5
{
  {   0.83529f,   0.89020f,   0.84706f },
  {   0.38039f,   0.54118f,   0.59608f },
  {   0.97647f,   0.85490f,   0.58431f },
  {   0.68235f,   0.29412f,   0.08627f },
  {   0.47059f,   0.43922f,   0.39216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
