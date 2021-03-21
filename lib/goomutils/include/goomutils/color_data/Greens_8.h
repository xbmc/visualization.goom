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
static const std::vector<vivid::srgb_t> Greens_8
{
  {   0.96863f,   0.98824f,   0.96078f },
  {   0.89804f,   0.96078f,   0.87843f },
  {   0.78039f,   0.91373f,   0.75294f },
  {   0.63137f,   0.85098f,   0.60784f },
  {   0.45490f,   0.76863f,   0.46275f },
  {   0.25490f,   0.67059f,   0.36471f },
  {   0.13725f,   0.54510f,   0.27059f },
  {   0.00000f,   0.35294f,   0.19608f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
