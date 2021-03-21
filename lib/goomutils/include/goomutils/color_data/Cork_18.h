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
static const std::vector<vivid::srgb_t> Cork_18
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16863f,   0.18431f,   0.38431f },
  {   0.16471f,   0.27451f,   0.47059f },
  {   0.20392f,   0.36863f,   0.55686f },
  {   0.30588f,   0.46667f,   0.63137f },
  {   0.43137f,   0.56863f,   0.70196f },
  {   0.56078f,   0.66667f,   0.76863f },
  {   0.69412f,   0.76863f,   0.83922f },
  {   0.81961f,   0.86667f,   0.89804f },
  {   0.84706f,   0.90588f,   0.86275f },
  {   0.74118f,   0.84706f,   0.75294f },
  {   0.62353f,   0.78039f,   0.63529f },
  {   0.50588f,   0.70980f,   0.52157f },
  {   0.38824f,   0.63922f,   0.40784f },
  {   0.29020f,   0.54902f,   0.28235f },
  {   0.25490f,   0.45098f,   0.16863f },
  {   0.25490f,   0.37255f,   0.08627f },
  {   0.25882f,   0.30196f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
