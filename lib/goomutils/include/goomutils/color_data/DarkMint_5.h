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
static const std::vector<vivid::srgb_t> DarkMint_5
{
  {   0.82353f,   0.98431f,   0.83137f },
  {   0.48235f,   0.73725f,   0.69020f },
  {   0.33333f,   0.61176f,   0.61961f },
  {   0.22745f,   0.48627f,   0.53725f },
  {   0.07059f,   0.24706f,   0.35294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
