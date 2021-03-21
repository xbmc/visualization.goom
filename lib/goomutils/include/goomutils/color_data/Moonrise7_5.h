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
static const std::vector<vivid::srgb_t> Moonrise7_5
{
  {   0.13725f,   0.13725f,   0.33333f },
  {   0.38039f,   0.40784f,   0.37647f },
  {   0.65490f,   0.35686f,   0.26667f },
  {   0.56863f,   0.16863f,   0.16078f },
  {   1.00000f,   0.89020f,   0.56078f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
