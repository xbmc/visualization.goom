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
static const std::vector<vivid::srgb_t> Matter_18
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98824f,   0.84706f,   0.61176f },
  {   0.97647f,   0.76471f,   0.54118f },
  {   0.96863f,   0.68627f,   0.47451f },
  {   0.95294f,   0.60392f,   0.41569f },
  {   0.93333f,   0.52549f,   0.36863f },
  {   0.91373f,   0.44706f,   0.33725f },
  {   0.87843f,   0.36863f,   0.32549f },
  {   0.83529f,   0.29804f,   0.32941f },
  {   0.78039f,   0.23922f,   0.34902f },
  {   0.71765f,   0.18824f,   0.36863f },
  {   0.64706f,   0.14902f,   0.38431f },
  {   0.57255f,   0.12157f,   0.38824f },
  {   0.49412f,   0.10588f,   0.38431f },
  {   0.41569f,   0.09804f,   0.36863f },
  {   0.33725f,   0.09020f,   0.33333f },
  {   0.25882f,   0.07843f,   0.29412f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
