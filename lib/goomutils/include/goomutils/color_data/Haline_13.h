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
static const std::vector<vivid::srgb_t> Haline_13
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.17647f,   0.12941f,   0.61569f },
  {   0.07843f,   0.26275f,   0.61176f },
  {   0.05882f,   0.35686f,   0.56471f },
  {   0.12549f,   0.43137f,   0.54510f },
  {   0.18431f,   0.50196f,   0.53725f },
  {   0.23529f,   0.57647f,   0.52941f },
  {   0.28235f,   0.65098f,   0.50980f },
  {   0.35294f,   0.72549f,   0.47059f },
  {   0.47059f,   0.79608f,   0.40784f },
  {   0.65882f,   0.84706f,   0.36078f },
  {   0.84706f,   0.88627f,   0.45098f },
  {   0.99216f,   0.93725f,   0.60392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
