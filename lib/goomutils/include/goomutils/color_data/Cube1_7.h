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
static const std::vector<vivid::srgb_t> Cube1_7
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.46667f,   0.31765f,   0.94902f },
  {   0.29804f,   0.61961f,   0.85098f },
  {   0.28627f,   0.81569f,   0.49412f },
  {   0.52157f,   0.92157f,   0.31373f },
  {   0.83529f,   0.90196f,   0.35686f },
  {   0.97647f,   0.58824f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
