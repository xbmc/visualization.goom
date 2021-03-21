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
static const std::vector<vivid::srgb_t> Roma_13
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.58824f,   0.29412f,   0.07059f },
  {   0.67059f,   0.45490f,   0.14118f },
  {   0.75686f,   0.63529f,   0.23529f },
  {   0.85098f,   0.81176f,   0.42745f },
  {   0.88627f,   0.90588f,   0.63922f },
  {   0.79216f,   0.92157f,   0.78824f },
  {   0.58431f,   0.86667f,   0.84314f },
  {   0.38039f,   0.74118f,   0.82745f },
  {   0.28235f,   0.59608f,   0.77255f },
  {   0.22353f,   0.45882f,   0.71373f },
  {   0.16863f,   0.32549f,   0.65490f },
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
