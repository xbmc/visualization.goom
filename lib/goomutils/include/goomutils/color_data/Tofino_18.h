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
static const std::vector<vivid::srgb_t> Tofino_18
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.71373f,   0.73725f,   0.92941f },
  {   0.55686f,   0.62745f,   0.86275f },
  {   0.40000f,   0.51373f,   0.77647f },
  {   0.27059f,   0.39608f,   0.64706f },
  {   0.19216f,   0.29804f,   0.49412f },
  {   0.13333f,   0.20784f,   0.34902f },
  {   0.08627f,   0.12941f,   0.21176f },
  {   0.05882f,   0.08235f,   0.10588f },
  {   0.05882f,   0.10588f,   0.07059f },
  {   0.08627f,   0.17647f,   0.09412f },
  {   0.12549f,   0.27059f,   0.14118f },
  {   0.17255f,   0.37255f,   0.19216f },
  {   0.23137f,   0.48235f,   0.25098f },
  {   0.34118f,   0.60392f,   0.32941f },
  {   0.50980f,   0.71373f,   0.42353f },
  {   0.68627f,   0.80784f,   0.51765f },
  {   0.85882f,   0.90196f,   0.60784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
