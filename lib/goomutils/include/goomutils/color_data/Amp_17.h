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
static const std::vector<vivid::srgb_t> Amp_17
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.91373f,   0.85490f,   0.83922f },
  {   0.88627f,   0.78039f,   0.74902f },
  {   0.86667f,   0.70980f,   0.65882f },
  {   0.84314f,   0.63529f,   0.56863f },
  {   0.82353f,   0.56471f,   0.47843f },
  {   0.80000f,   0.49412f,   0.39216f },
  {   0.77647f,   0.41961f,   0.30588f },
  {   0.75294f,   0.34510f,   0.23137f },
  {   0.72549f,   0.27059f,   0.17255f },
  {   0.68627f,   0.18824f,   0.14118f },
  {   0.63137f,   0.11373f,   0.14510f },
  {   0.56471f,   0.06275f,   0.16078f },
  {   0.48235f,   0.05490f,   0.16078f },
  {   0.39608f,   0.05882f,   0.14118f },
  {   0.31765f,   0.05098f,   0.10980f },
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
