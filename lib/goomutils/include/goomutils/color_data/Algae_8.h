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
static const std::vector<vivid::srgb_t> Algae_8
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.66667f,   0.85490f,   0.61569f },
  {   0.46667f,   0.74118f,   0.43529f },
  {   0.20392f,   0.63922f,   0.32549f },
  {   0.02745f,   0.51765f,   0.30196f },
  {   0.08627f,   0.38824f,   0.25098f },
  {   0.10196f,   0.26275f,   0.17255f },
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
