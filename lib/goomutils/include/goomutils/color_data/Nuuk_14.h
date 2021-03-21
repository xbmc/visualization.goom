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
static const std::vector<vivid::srgb_t> Nuuk_14
{
  {   0.01961f,   0.34902f,   0.54902f },
  {   0.12941f,   0.37255f,   0.52549f },
  {   0.20784f,   0.40392f,   0.50980f },
  {   0.30196f,   0.45098f,   0.51765f },
  {   0.40000f,   0.50588f,   0.54118f },
  {   0.50196f,   0.56863f,   0.57255f },
  {   0.59216f,   0.62353f,   0.59216f },
  {   0.65882f,   0.67059f,   0.59216f },
  {   0.70588f,   0.70588f,   0.57255f },
  {   0.74118f,   0.73725f,   0.54118f },
  {   0.77255f,   0.77255f,   0.51765f },
  {   0.83137f,   0.83137f,   0.52549f },
  {   0.91373f,   0.91373f,   0.59216f },
  {   0.99608f,   0.99608f,   0.69804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
