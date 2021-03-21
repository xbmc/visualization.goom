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
static const std::vector<vivid::srgb_t> Batlow_16
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.03922f,   0.16863f,   0.36078f },
  {   0.06275f,   0.23922f,   0.37255f },
  {   0.09412f,   0.30980f,   0.38039f },
  {   0.15686f,   0.37647f,   0.37255f },
  {   0.24314f,   0.42353f,   0.33333f },
  {   0.34118f,   0.46275f,   0.27843f },
  {   0.44314f,   0.49412f,   0.22353f },
  {   0.56078f,   0.52549f,   0.18431f },
  {   0.69804f,   0.55294f,   0.19608f },
  {   0.83529f,   0.58039f,   0.28235f },
  {   0.93725f,   0.61176f,   0.41176f },
  {   0.98824f,   0.65490f,   0.55294f },
  {   0.99216f,   0.70196f,   0.69412f },
  {   0.98824f,   0.74902f,   0.83529f },
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
