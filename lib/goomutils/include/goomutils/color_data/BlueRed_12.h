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
static const std::vector<vivid::srgb_t> BlueRed_12
{
  {   0.17255f,   0.41176f,   0.69020f },
  {   0.70980f,   0.78431f,   0.88627f },
  {   0.94118f,   0.15294f,   0.12549f },
  {   1.00000f,   0.71373f,   0.69020f },
  {   0.67451f,   0.38039f,   0.23529f },
  {   0.91373f,   0.76471f,   0.60784f },
  {   0.41961f,   0.63922f,   0.83922f },
  {   0.70980f,   0.87451f,   0.99216f },
  {   0.67451f,   0.52941f,   0.38824f },
  {   0.86667f,   0.78824f,   0.70588f },
  {   0.74118f,   0.03922f,   0.21176f },
  {   0.95686f,   0.45098f,   0.47843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
