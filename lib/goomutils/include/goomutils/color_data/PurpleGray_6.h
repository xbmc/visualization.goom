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
static const std::vector<vivid::srgb_t> PurpleGray_6
{
  {   0.48235f,   0.40000f,   0.82353f },
  {   0.86275f,   0.37255f,   0.74118f },
  {   0.58039f,   0.56863f,   0.48235f },
  {   0.60000f,   0.33725f,   0.53333f },
  {   0.81569f,   0.59608f,   0.93333f },
  {   0.84314f,   0.83529f,   0.77255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
