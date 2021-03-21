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
static const std::vector<vivid::srgb_t> Turku_16
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.09804f,   0.09804f,   0.09020f },
  {   0.16471f,   0.16471f,   0.14510f },
  {   0.23529f,   0.23529f,   0.19608f },
  {   0.30588f,   0.30196f,   0.23529f },
  {   0.37255f,   0.37255f,   0.26667f },
  {   0.44314f,   0.43922f,   0.29804f },
  {   0.52549f,   0.50980f,   0.33333f },
  {   0.62353f,   0.58039f,   0.38039f },
  {   0.72549f,   0.62745f,   0.43137f },
  {   0.81176f,   0.65098f,   0.48627f },
  {   0.87843f,   0.66275f,   0.54510f },
  {   0.93725f,   0.69412f,   0.63137f },
  {   0.98039f,   0.75686f,   0.72941f },
  {   0.99608f,   0.82745f,   0.81961f },
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
