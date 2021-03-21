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
static const std::vector<vivid::srgb_t> Imola_11
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.13725f,   0.27059f,   0.66667f },
  {   0.17255f,   0.33333f,   0.63137f },
  {   0.20784f,   0.39608f,   0.59608f },
  {   0.25882f,   0.45490f,   0.54510f },
  {   0.32941f,   0.52549f,   0.49804f },
  {   0.41569f,   0.61569f,   0.47059f },
  {   0.51373f,   0.71373f,   0.44706f },
  {   0.62353f,   0.82353f,   0.41961f },
  {   0.79216f,   0.92549f,   0.40392f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
