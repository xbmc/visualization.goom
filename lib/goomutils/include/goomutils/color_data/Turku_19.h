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
static const std::vector<vivid::srgb_t> Turku_19
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.08627f,   0.08627f,   0.07843f },
  {   0.14118f,   0.14118f,   0.12549f },
  {   0.20000f,   0.19608f,   0.16863f },
  {   0.25882f,   0.25882f,   0.20784f },
  {   0.31765f,   0.31373f,   0.23922f },
  {   0.37255f,   0.37255f,   0.26667f },
  {   0.43137f,   0.42745f,   0.29412f },
  {   0.49412f,   0.48627f,   0.32157f },
  {   0.57647f,   0.54902f,   0.35686f },
  {   0.66275f,   0.60000f,   0.39608f },
  {   0.74510f,   0.63529f,   0.43922f },
  {   0.81176f,   0.65098f,   0.48627f },
  {   0.86667f,   0.65882f,   0.53333f },
  {   0.91765f,   0.67843f,   0.59608f },
  {   0.96078f,   0.72157f,   0.67843f },
  {   0.98824f,   0.78039f,   0.76471f },
  {   0.99608f,   0.84314f,   0.83529f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
