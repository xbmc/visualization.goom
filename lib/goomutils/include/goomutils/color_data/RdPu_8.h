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
static const std::vector<vivid::srgb_t> RdPu_8
{
  {   1.00000f,   0.96863f,   0.95294f },
  {   0.99216f,   0.87843f,   0.86667f },
  {   0.98824f,   0.77255f,   0.75294f },
  {   0.98039f,   0.62353f,   0.70980f },
  {   0.96863f,   0.40784f,   0.63137f },
  {   0.86667f,   0.20392f,   0.59216f },
  {   0.68235f,   0.00392f,   0.49412f },
  {   0.47843f,   0.00392f,   0.46667f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
