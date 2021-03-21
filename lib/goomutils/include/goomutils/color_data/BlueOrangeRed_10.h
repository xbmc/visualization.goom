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
static const std::vector<vivid::srgb_t> BlueOrangeRed_10
{
  {   0.02745f,   0.35294f,   1.00000f },
  {   0.19608f,   0.46275f,   1.00000f },
  {   0.54902f,   0.69804f,   1.00000f },
  {   0.74902f,   0.83137f,   1.00000f },
  {   0.96863f,   0.97647f,   1.00000f },
  {   1.00000f,   1.00000f,   0.80000f },
  {   1.00000f,   1.00000f,   0.00000f },
  {   1.00000f,   0.80000f,   0.00000f },
  {   1.00000f,   0.40000f,   0.00000f },
  {   1.00000f,   0.00000f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
