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
static const std::vector<vivid::srgb_t> Cube1_8
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.49020f,   0.27059f,   0.89412f },
  {   0.34902f,   0.54902f,   0.92549f },
  {   0.23137f,   0.74510f,   0.66275f },
  {   0.33725f,   0.87059f,   0.32157f },
  {   0.63529f,   0.92549f,   0.33333f },
  {   0.86275f,   0.86667f,   0.36078f },
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
