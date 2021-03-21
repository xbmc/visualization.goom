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
static const std::vector<vivid::srgb_t> Bilbao_18
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.92549f,   0.92549f,   0.92157f },
  {   0.85490f,   0.85098f,   0.83922f },
  {   0.80000f,   0.78824f,   0.75294f },
  {   0.76471f,   0.74510f,   0.67059f },
  {   0.74118f,   0.70980f,   0.59608f },
  {   0.71765f,   0.67059f,   0.51765f },
  {   0.69412f,   0.61176f,   0.45098f },
  {   0.67451f,   0.55686f,   0.41176f },
  {   0.65882f,   0.50196f,   0.38824f },
  {   0.64314f,   0.45098f,   0.36471f },
  {   0.62745f,   0.40000f,   0.34118f },
  {   0.60392f,   0.34118f,   0.30980f },
  {   0.56471f,   0.27843f,   0.26667f },
  {   0.50588f,   0.21176f,   0.20392f },
  {   0.43922f,   0.14510f,   0.14118f },
  {   0.37255f,   0.07451f,   0.08235f },
  {   0.30196f,   0.00000f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
