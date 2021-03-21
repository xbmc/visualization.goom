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
static const std::vector<vivid::srgb_t> Buda_12
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.70196f,   0.14510f,   0.63137f },
  {   0.71373f,   0.23922f,   0.58824f },
  {   0.74118f,   0.32941f,   0.55686f },
  {   0.76863f,   0.40784f,   0.53333f },
  {   0.79216f,   0.48235f,   0.50588f },
  {   0.81569f,   0.56078f,   0.48627f },
  {   0.83529f,   0.63922f,   0.46667f },
  {   0.85490f,   0.71765f,   0.44706f },
  {   0.87843f,   0.80392f,   0.42353f },
  {   0.90980f,   0.89412f,   0.40392f },
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
