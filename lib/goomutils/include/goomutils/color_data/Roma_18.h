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
static const std::vector<vivid::srgb_t> Roma_18
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.56471f,   0.24314f,   0.05098f },
  {   0.62353f,   0.36471f,   0.10196f },
  {   0.67843f,   0.47843f,   0.15294f },
  {   0.73725f,   0.60000f,   0.21176f },
  {   0.80784f,   0.73333f,   0.32157f },
  {   0.87059f,   0.84706f,   0.48235f },
  {   0.89020f,   0.90588f,   0.63137f },
  {   0.84314f,   0.92157f,   0.74510f },
  {   0.73333f,   0.91373f,   0.81569f },
  {   0.57255f,   0.86275f,   0.84314f },
  {   0.41961f,   0.77647f,   0.83529f },
  {   0.32549f,   0.67059f,   0.80000f },
  {   0.27059f,   0.56863f,   0.76078f },
  {   0.22745f,   0.47059f,   0.71765f },
  {   0.18824f,   0.38039f,   0.67843f },
  {   0.15294f,   0.29020f,   0.63922f },
  {   0.10196f,   0.20000f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
