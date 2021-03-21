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
static const std::vector<vivid::srgb_t> Balance_12
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.16078f,   0.23137f,   0.56078f },
  {   0.04314f,   0.40000f,   0.74118f },
  {   0.28235f,   0.57255f,   0.72941f },
  {   0.55686f,   0.70980f,   0.76471f },
  {   0.82745f,   0.85098f,   0.86275f },
  {   0.90196f,   0.82353f,   0.80392f },
  {   0.83922f,   0.61569f,   0.54118f },
  {   0.77255f,   0.40784f,   0.29412f },
  {   0.67451f,   0.16863f,   0.14118f },
  {   0.47059f,   0.05490f,   0.15686f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
