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
static const std::vector<vivid::srgb_t> Roma_16
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.57255f,   0.25882f,   0.05882f },
  {   0.63922f,   0.39608f,   0.11373f },
  {   0.70196f,   0.52549f,   0.17255f },
  {   0.77255f,   0.67059f,   0.26275f },
  {   0.85098f,   0.81176f,   0.42745f },
  {   0.89020f,   0.89804f,   0.60392f },
  {   0.85098f,   0.92157f,   0.73725f },
  {   0.72157f,   0.90980f,   0.81961f },
  {   0.54118f,   0.84706f,   0.84706f },
  {   0.38039f,   0.74118f,   0.82745f },
  {   0.29412f,   0.62353f,   0.78039f },
  {   0.24314f,   0.50980f,   0.73333f },
  {   0.20000f,   0.40392f,   0.68627f },
  {   0.15686f,   0.30196f,   0.64314f },
  {   0.10196f,   0.20000f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
