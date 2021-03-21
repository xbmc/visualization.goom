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
static const std::vector<vivid::srgb_t> Cube1_5
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.38431f,   0.49020f,   0.96471f },
  {   0.28627f,   0.81569f,   0.49412f },
  {   0.71373f,   0.92549f,   0.34118f },
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
