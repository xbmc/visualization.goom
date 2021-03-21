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
static const std::vector<vivid::srgb_t> Vik_18
{
  {   0.00000f,   0.07059f,   0.38039f },
  {   0.00784f,   0.16471f,   0.43922f },
  {   0.01176f,   0.25490f,   0.49804f },
  {   0.03137f,   0.34902f,   0.56078f },
  {   0.14510f,   0.45882f,   0.63137f },
  {   0.31765f,   0.58039f,   0.71373f },
  {   0.50196f,   0.69804f,   0.79216f },
  {   0.69020f,   0.81176f,   0.87059f },
  {   0.87059f,   0.90196f,   0.91373f },
  {   0.93333f,   0.85882f,   0.81569f },
  {   0.89412f,   0.74510f,   0.65882f },
  {   0.84314f,   0.62745f,   0.50588f },
  {   0.80000f,   0.52157f,   0.36471f },
  {   0.75294f,   0.41961f,   0.22745f },
  {   0.68627f,   0.29804f,   0.09412f },
  {   0.56078f,   0.16863f,   0.02353f },
  {   0.45098f,   0.07843f,   0.02353f },
  {   0.34902f,   0.00000f,   0.03137f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
