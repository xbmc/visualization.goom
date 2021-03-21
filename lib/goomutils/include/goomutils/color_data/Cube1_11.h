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
static const std::vector<vivid::srgb_t> Cube1_11
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.50588f,   0.14902f,   0.80392f },
  {   0.43137f,   0.38431f,   0.99216f },
  {   0.33725f,   0.56863f,   0.90980f },
  {   0.21961f,   0.71373f,   0.72157f },
  {   0.28627f,   0.81569f,   0.49412f },
  {   0.36078f,   0.89020f,   0.28627f },
  {   0.59608f,   0.92549f,   0.32549f },
  {   0.80000f,   0.92549f,   0.35294f },
  {   0.91765f,   0.80392f,   0.36471f },
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
