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
static const std::vector<vivid::srgb_t> Acton_16
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.24706f,   0.18824f,   0.36078f },
  {   0.32157f,   0.25098f,   0.42353f },
  {   0.40000f,   0.31373f,   0.48235f },
  {   0.49020f,   0.36078f,   0.53333f },
  {   0.57255f,   0.38824f,   0.56471f },
  {   0.65098f,   0.40000f,   0.58039f },
  {   0.72549f,   0.41176f,   0.59216f },
  {   0.80000f,   0.45882f,   0.63137f },
  {   0.83137f,   0.52549f,   0.67843f },
  {   0.83137f,   0.58431f,   0.72157f },
  {   0.82745f,   0.63922f,   0.76078f },
  {   0.83529f,   0.69804f,   0.80392f },
  {   0.85098f,   0.76471f,   0.84706f },
  {   0.87451f,   0.83137f,   0.89412f },
  {   0.90196f,   0.90196f,   0.94118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
