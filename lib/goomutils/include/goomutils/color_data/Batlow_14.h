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
static const std::vector<vivid::srgb_t> Batlow_14
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.04314f,   0.18039f,   0.36471f },
  {   0.07059f,   0.25882f,   0.37647f },
  {   0.11765f,   0.34118f,   0.38039f },
  {   0.20392f,   0.40784f,   0.35294f },
  {   0.31765f,   0.45490f,   0.29412f },
  {   0.43922f,   0.49020f,   0.22745f },
  {   0.56863f,   0.52549f,   0.18039f },
  {   0.73333f,   0.56078f,   0.21176f },
  {   0.88235f,   0.59216f,   0.33333f },
  {   0.97255f,   0.63529f,   0.48627f },
  {   0.99216f,   0.68627f,   0.65098f },
  {   0.99216f,   0.74118f,   0.80784f },
  {   0.98039f,   0.80000f,   0.98039f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
