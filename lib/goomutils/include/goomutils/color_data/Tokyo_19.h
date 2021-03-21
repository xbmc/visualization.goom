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
static const std::vector<vivid::srgb_t> Tokyo_19
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.18824f,   0.08627f,   0.24706f },
  {   0.27059f,   0.12549f,   0.29804f },
  {   0.35294f,   0.17647f,   0.34902f },
  {   0.43137f,   0.24314f,   0.40392f },
  {   0.48627f,   0.30980f,   0.44314f },
  {   0.52157f,   0.36863f,   0.47059f },
  {   0.54118f,   0.42353f,   0.49412f },
  {   0.55294f,   0.47451f,   0.50980f },
  {   0.56471f,   0.52941f,   0.52549f },
  {   0.57255f,   0.58039f,   0.53725f },
  {   0.58039f,   0.63137f,   0.55294f },
  {   0.59216f,   0.68235f,   0.56863f },
  {   0.61176f,   0.74118f,   0.58431f },
  {   0.65490f,   0.80784f,   0.61569f },
  {   0.72941f,   0.88235f,   0.66667f },
  {   0.83529f,   0.94902f,   0.73725f },
  {   0.92549f,   0.98039f,   0.79608f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
