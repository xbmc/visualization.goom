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
static const std::vector<vivid::srgb_t> Buda_18
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.70196f,   0.10588f,   0.65098f },
  {   0.70196f,   0.17647f,   0.61569f },
  {   0.71373f,   0.23529f,   0.58824f },
  {   0.72941f,   0.29412f,   0.56863f },
  {   0.74902f,   0.34510f,   0.55294f },
  {   0.76471f,   0.39608f,   0.53333f },
  {   0.78039f,   0.44706f,   0.51765f },
  {   0.79608f,   0.49412f,   0.50196f },
  {   0.81176f,   0.54510f,   0.49020f },
  {   0.82353f,   0.59608f,   0.47451f },
  {   0.83922f,   0.64706f,   0.46275f },
  {   0.85098f,   0.70196f,   0.45098f },
  {   0.86275f,   0.75294f,   0.43529f },
  {   0.87843f,   0.80784f,   0.42353f },
  {   0.89412f,   0.86667f,   0.41176f },
  {   0.93333f,   0.92941f,   0.40392f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
