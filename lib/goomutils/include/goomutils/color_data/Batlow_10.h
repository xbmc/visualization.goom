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
static const std::vector<vivid::srgb_t> Batlow_10
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.05490f,   0.21176f,   0.36863f },
  {   0.11373f,   0.33333f,   0.38039f },
  {   0.24314f,   0.42353f,   0.33333f },
  {   0.40784f,   0.48235f,   0.24314f },
  {   0.60784f,   0.53333f,   0.18039f },
  {   0.83529f,   0.58039f,   0.28235f },
  {   0.97647f,   0.63922f,   0.50196f },
  {   0.99216f,   0.71765f,   0.74118f },
  {   0.98039f,   0.80000f,   0.98039f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
