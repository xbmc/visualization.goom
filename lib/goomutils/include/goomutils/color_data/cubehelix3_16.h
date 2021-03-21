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
static const std::vector<vivid::srgb_t> cubehelix3_16
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.00000f,   0.15294f,   0.04706f },
  {   0.00000f,   0.26667f,   0.23529f },
  {   0.00000f,   0.31373f,   0.51373f },
  {   0.01176f,   0.29412f,   0.79216f },
  {   0.28235f,   0.23529f,   0.98824f },
  {   0.61176f,   0.16863f,   1.00000f },
  {   0.92157f,   0.14118f,   0.95686f },
  {   1.00000f,   0.17647f,   0.76078f },
  {   1.00000f,   0.28627f,   0.52549f },
  {   1.00000f,   0.45098f,   0.33725f },
  {   1.00000f,   0.64314f,   0.26275f },
  {   0.92157f,   0.81961f,   0.33333f },
  {   0.82745f,   0.94510f,   0.52941f },
  {   0.84314f,   1.00000f,   0.78431f },
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
