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
static const std::vector<vivid::srgb_t> Cube1_16
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.51373f,   0.05098f,   0.70980f },
  {   0.49412f,   0.25098f,   0.87843f },
  {   0.43137f,   0.38431f,   0.99216f },
  {   0.36863f,   0.51765f,   0.94902f },
  {   0.29804f,   0.61961f,   0.85098f },
  {   0.21961f,   0.71373f,   0.72157f },
  {   0.26275f,   0.78431f,   0.57647f },
  {   0.30980f,   0.83922f,   0.42353f },
  {   0.36078f,   0.89020f,   0.28627f },
  {   0.52157f,   0.92157f,   0.31373f },
  {   0.67843f,   0.92549f,   0.33725f },
  {   0.80000f,   0.92549f,   0.35294f },
  {   0.87059f,   0.85490f,   0.36078f },
  {   0.95294f,   0.74510f,   0.36863f },
  {   0.97647f,   0.58824f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
