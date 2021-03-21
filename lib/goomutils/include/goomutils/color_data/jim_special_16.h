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
static const std::vector<vivid::srgb_t> jim_special_16
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.08627f,   0.03922f,   0.13333f },
  {   0.14510f,   0.09804f,   0.26667f },
  {   0.18431f,   0.16863f,   0.38824f },
  {   0.20392f,   0.25490f,   0.49020f },
  {   0.21569f,   0.34510f,   0.57255f },
  {   0.23137f,   0.43922f,   0.62745f },
  {   0.25098f,   0.53725f,   0.66275f },
  {   0.29020f,   0.62745f,   0.67843f },
  {   0.34902f,   0.70980f,   0.68627f },
  {   0.42745f,   0.78039f,   0.69412f },
  {   0.52549f,   0.83922f,   0.70588f },
  {   0.63922f,   0.89020f,   0.74118f },
  {   0.76471f,   0.92941f,   0.79608f },
  {   0.88627f,   0.96471f,   0.88235f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
