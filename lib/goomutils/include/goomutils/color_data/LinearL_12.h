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
static const std::vector<vivid::srgb_t> LinearL_12
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.16863f,   0.07451f,   0.14902f },
  {   0.17255f,   0.12549f,   0.43137f },
  {   0.10588f,   0.24706f,   0.52157f },
  {   0.01176f,   0.37647f,   0.43922f },
  {   0.00000f,   0.49804f,   0.32157f },
  {   0.00000f,   0.61569f,   0.19608f },
  {   0.23922f,   0.70588f,   0.00000f },
  {   0.58431f,   0.76863f,   0.00000f },
  {   0.85882f,   0.80784f,   0.47451f },
  {   0.96863f,   0.88627f,   0.81961f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
