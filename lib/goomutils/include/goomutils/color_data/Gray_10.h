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
static const std::vector<vivid::srgb_t> Gray_10
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.08627f,   0.08235f,   0.08235f },
  {   0.19216f,   0.18824f,   0.18824f },
  {   0.29020f,   0.29020f,   0.28627f },
  {   0.39216f,   0.38824f,   0.38824f },
  {   0.49804f,   0.49412f,   0.49412f },
  {   0.60784f,   0.60392f,   0.60392f },
  {   0.72549f,   0.72549f,   0.72157f },
  {   0.85882f,   0.85490f,   0.85098f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
