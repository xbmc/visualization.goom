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
static const std::vector<vivid::srgb_t> Roma_20
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.55294f,   0.22745f,   0.04314f },
  {   0.61176f,   0.34118f,   0.09020f },
  {   0.66275f,   0.44314f,   0.13333f },
  {   0.71373f,   0.54902f,   0.18431f },
  {   0.76863f,   0.65882f,   0.25490f },
  {   0.83529f,   0.78431f,   0.38039f },
  {   0.87843f,   0.86667f,   0.52549f },
  {   0.88627f,   0.90980f,   0.65098f },
  {   0.83922f,   0.92549f,   0.75294f },
  {   0.74118f,   0.91373f,   0.81176f },
  {   0.59608f,   0.87451f,   0.84314f },
  {   0.45882f,   0.80000f,   0.83922f },
  {   0.35686f,   0.71373f,   0.81569f },
  {   0.29020f,   0.61569f,   0.78039f },
  {   0.25098f,   0.52941f,   0.74118f },
  {   0.21569f,   0.43922f,   0.70588f },
  {   0.18431f,   0.36078f,   0.67059f },
  {   0.14510f,   0.27843f,   0.63137f },
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
