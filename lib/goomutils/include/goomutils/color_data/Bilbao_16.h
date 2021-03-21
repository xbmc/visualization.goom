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
static const std::vector<vivid::srgb_t> Bilbao_16
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.91373f,   0.91373f,   0.90980f },
  {   0.83529f,   0.83137f,   0.81569f },
  {   0.78431f,   0.76863f,   0.72157f },
  {   0.75294f,   0.72549f,   0.63137f },
  {   0.72549f,   0.68627f,   0.54510f },
  {   0.69804f,   0.62353f,   0.46275f },
  {   0.67451f,   0.56078f,   0.41176f },
  {   0.65882f,   0.49804f,   0.38431f },
  {   0.63922f,   0.43922f,   0.36078f },
  {   0.61961f,   0.38039f,   0.33333f },
  {   0.58824f,   0.31373f,   0.29412f },
  {   0.53333f,   0.23529f,   0.23137f },
  {   0.45882f,   0.16078f,   0.15686f },
  {   0.38039f,   0.08627f,   0.09020f },
  {   0.30196f,   0.00000f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
