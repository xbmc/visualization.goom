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
static const std::vector<vivid::srgb_t> Algae_14
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.74510f,   0.90588f,   0.70196f },
  {   0.65098f,   0.84314f,   0.60000f },
  {   0.54510f,   0.78039f,   0.50196f },
  {   0.43529f,   0.72549f,   0.41569f },
  {   0.29804f,   0.67059f,   0.34510f },
  {   0.13333f,   0.61176f,   0.31765f },
  {   0.03529f,   0.54902f,   0.30980f },
  {   0.04314f,   0.47843f,   0.28627f },
  {   0.07843f,   0.40784f,   0.25882f },
  {   0.09804f,   0.34118f,   0.22353f },
  {   0.10196f,   0.27451f,   0.18039f },
  {   0.09020f,   0.20784f,   0.13333f },
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
