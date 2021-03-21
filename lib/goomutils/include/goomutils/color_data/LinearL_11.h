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
static const std::vector<vivid::srgb_t> LinearL_11
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.18039f,   0.07843f,   0.17647f },
  {   0.15686f,   0.14902f,   0.47059f },
  {   0.09804f,   0.27843f,   0.53333f },
  {   0.00000f,   0.42353f,   0.39608f },
  {   0.00000f,   0.55686f,   0.24706f },
  {   0.07843f,   0.67059f,   0.00000f },
  {   0.44706f,   0.75686f,   0.00000f },
  {   0.81961f,   0.79608f,   0.34118f },
  {   0.97255f,   0.87451f,   0.80000f },
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
