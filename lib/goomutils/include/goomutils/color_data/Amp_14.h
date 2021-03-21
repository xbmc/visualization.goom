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
static const std::vector<vivid::srgb_t> Amp_14
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.90588f,   0.83529f,   0.81569f },
  {   0.87843f,   0.74902f,   0.70980f },
  {   0.85098f,   0.65882f,   0.59608f },
  {   0.82353f,   0.57255f,   0.49020f },
  {   0.79608f,   0.48627f,   0.38039f },
  {   0.76863f,   0.39216f,   0.27843f },
  {   0.73725f,   0.30196f,   0.19216f },
  {   0.69020f,   0.20000f,   0.14510f },
  {   0.62353f,   0.10588f,   0.14902f },
  {   0.53725f,   0.05882f,   0.16078f },
  {   0.43529f,   0.05490f,   0.14902f },
  {   0.33725f,   0.05490f,   0.11765f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
