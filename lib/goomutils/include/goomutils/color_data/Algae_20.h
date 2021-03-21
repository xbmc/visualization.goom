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
static const std::vector<vivid::srgb_t> Algae_20
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.78039f,   0.92941f,   0.74118f },
  {   0.70980f,   0.88235f,   0.66275f },
  {   0.64314f,   0.83922f,   0.59608f },
  {   0.57255f,   0.79608f,   0.52549f },
  {   0.50196f,   0.75686f,   0.46275f },
  {   0.41961f,   0.71765f,   0.40392f },
  {   0.32941f,   0.68235f,   0.35686f },
  {   0.22353f,   0.64706f,   0.32549f },
  {   0.10980f,   0.60392f,   0.31765f },
  {   0.04314f,   0.56078f,   0.30980f },
  {   0.02745f,   0.50980f,   0.29804f },
  {   0.05098f,   0.46275f,   0.28235f },
  {   0.07451f,   0.41569f,   0.26275f },
  {   0.09412f,   0.36863f,   0.23922f },
  {   0.10196f,   0.32549f,   0.21176f },
  {   0.10196f,   0.27843f,   0.18039f },
  {   0.09412f,   0.23137f,   0.14902f },
  {   0.08627f,   0.18431f,   0.11373f },
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
