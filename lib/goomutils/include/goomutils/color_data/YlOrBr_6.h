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
static const std::vector<vivid::srgb_t> YlOrBr_6
{
  {   1.00000f,   1.00000f,   0.83137f },
  {   0.99608f,   0.89020f,   0.56863f },
  {   0.99608f,   0.76863f,   0.30980f },
  {   0.99608f,   0.60000f,   0.16078f },
  {   0.85098f,   0.37255f,   0.05490f },
  {   0.60000f,   0.20392f,   0.01569f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
