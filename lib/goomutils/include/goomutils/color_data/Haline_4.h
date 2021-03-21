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
static const std::vector<vivid::srgb_t> Haline_4
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.12549f,   0.43137f,   0.54510f },
  {   0.35294f,   0.72549f,   0.47059f },
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
