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
static const std::vector<vivid::srgb_t> Bilbao_20
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.93333f,   0.93333f,   0.93333f },
  {   0.86667f,   0.86275f,   0.85490f },
  {   0.81569f,   0.80784f,   0.78039f },
  {   0.77647f,   0.76078f,   0.70196f },
  {   0.75294f,   0.72941f,   0.63529f },
  {   0.73333f,   0.69412f,   0.56471f },
  {   0.70980f,   0.65490f,   0.49804f },
  {   0.69020f,   0.60392f,   0.44314f },
  {   0.67451f,   0.55294f,   0.40784f },
  {   0.65882f,   0.50588f,   0.38824f },
  {   0.64706f,   0.45882f,   0.36863f },
  {   0.63137f,   0.41176f,   0.34902f },
  {   0.61569f,   0.36471f,   0.32549f },
  {   0.58824f,   0.30980f,   0.29020f },
  {   0.54510f,   0.25098f,   0.24314f },
  {   0.48627f,   0.18824f,   0.18431f },
  {   0.42745f,   0.12941f,   0.12941f },
  {   0.36078f,   0.06667f,   0.07451f },
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
