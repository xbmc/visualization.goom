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
static const std::vector<vivid::srgb_t> Greens_6
{
  {   0.92941f,   0.97255f,   0.91373f },
  {   0.78039f,   0.91373f,   0.75294f },
  {   0.63137f,   0.85098f,   0.60784f },
  {   0.45490f,   0.76863f,   0.46275f },
  {   0.19216f,   0.63922f,   0.32941f },
  {   0.00000f,   0.42745f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
