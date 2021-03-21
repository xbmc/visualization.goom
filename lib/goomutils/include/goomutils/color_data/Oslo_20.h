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
static const std::vector<vivid::srgb_t> Oslo_20
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.03137f,   0.05882f,   0.09020f },
  {   0.05098f,   0.10196f,   0.15686f },
  {   0.05882f,   0.14118f,   0.22353f },
  {   0.07059f,   0.18824f,   0.29804f },
  {   0.09020f,   0.23137f,   0.37647f },
  {   0.11373f,   0.28235f,   0.45882f },
  {   0.14510f,   0.33333f,   0.53725f },
  {   0.19216f,   0.38431f,   0.61961f },
  {   0.26667f,   0.44706f,   0.70196f },
  {   0.34902f,   0.50980f,   0.76078f },
  {   0.43137f,   0.56471f,   0.78431f },
  {   0.49412f,   0.60392f,   0.79216f },
  {   0.55294f,   0.63922f,   0.78824f },
  {   0.61961f,   0.68235f,   0.78824f },
  {   0.68235f,   0.72549f,   0.79608f },
  {   0.76078f,   0.78039f,   0.81961f },
  {   0.83529f,   0.84706f,   0.86275f },
  {   0.92157f,   0.92549f,   0.92941f },
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
