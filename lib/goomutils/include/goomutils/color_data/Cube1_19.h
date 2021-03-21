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
static const std::vector<vivid::srgb_t> Cube1_19
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.51373f,   0.03922f,   0.67843f },
  {   0.50588f,   0.17647f,   0.82353f },
  {   0.46667f,   0.31765f,   0.94902f },
  {   0.40784f,   0.43529f,   0.98431f },
  {   0.35686f,   0.53725f,   0.93725f },
  {   0.29804f,   0.61961f,   0.85098f },
  {   0.22353f,   0.69804f,   0.74510f },
  {   0.24314f,   0.76078f,   0.62745f },
  {   0.28627f,   0.81569f,   0.49412f },
  {   0.32549f,   0.85882f,   0.36471f },
  {   0.38039f,   0.89804f,   0.28627f },
  {   0.52157f,   0.92157f,   0.31373f },
  {   0.65490f,   0.92549f,   0.33333f },
  {   0.76471f,   0.92549f,   0.34902f },
  {   0.83529f,   0.90196f,   0.35686f },
  {   0.90196f,   0.82353f,   0.36471f },
  {   0.95686f,   0.72157f,   0.36863f },
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
