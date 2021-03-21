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
static const std::vector<vivid::srgb_t> perceptual_rainbow_16
{
  {   0.52941f,   0.23137f,   0.38039f },
  {   0.56078f,   0.25098f,   0.49804f },
  {   0.56078f,   0.28235f,   0.61569f },
  {   0.52941f,   0.33333f,   0.72549f },
  {   0.47451f,   0.40000f,   0.81176f },
  {   0.40392f,   0.48235f,   0.86275f },
  {   0.32941f,   0.57255f,   0.87451f },
  {   0.27059f,   0.66667f,   0.84314f },
  {   0.23137f,   0.75294f,   0.77255f },
  {   0.23529f,   0.82353f,   0.67451f },
  {   0.27843f,   0.87451f,   0.56863f },
  {   0.36471f,   0.89804f,   0.47059f },
  {   0.48627f,   0.90588f,   0.40392f },
  {   0.63137f,   0.89020f,   0.37255f },
  {   0.77647f,   0.86275f,   0.39216f },
  {   0.91373f,   0.83529f,   0.45882f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
