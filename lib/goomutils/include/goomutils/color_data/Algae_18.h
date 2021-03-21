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
static const std::vector<vivid::srgb_t> Algae_18
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.76863f,   0.92157f,   0.72941f },
  {   0.69412f,   0.87059f,   0.64706f },
  {   0.61961f,   0.82353f,   0.56863f },
  {   0.54118f,   0.78039f,   0.49412f },
  {   0.45490f,   0.73333f,   0.42745f },
  {   0.35686f,   0.69412f,   0.36863f },
  {   0.23922f,   0.65098f,   0.32941f },
  {   0.11765f,   0.60784f,   0.31765f },
  {   0.03922f,   0.55686f,   0.30980f },
  {   0.03137f,   0.50196f,   0.29412f },
  {   0.05882f,   0.45098f,   0.27843f },
  {   0.08235f,   0.39608f,   0.25098f },
  {   0.09804f,   0.34510f,   0.22353f },
  {   0.10196f,   0.29412f,   0.19216f },
  {   0.09804f,   0.24314f,   0.15686f },
  {   0.08627f,   0.19216f,   0.11765f },
  {   0.07059f,   0.14118f,   0.07843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
