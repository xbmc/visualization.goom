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
static const std::vector<vivid::srgb_t> Batlow_18
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.03529f,   0.16078f,   0.36078f },
  {   0.05882f,   0.21961f,   0.37255f },
  {   0.08235f,   0.28235f,   0.38039f },
  {   0.12157f,   0.34510f,   0.38039f },
  {   0.18824f,   0.40000f,   0.35686f },
  {   0.27059f,   0.43529f,   0.31765f },
  {   0.36078f,   0.46667f,   0.27059f },
  {   0.45098f,   0.49412f,   0.21961f },
  {   0.55294f,   0.52157f,   0.18431f },
  {   0.67451f,   0.54902f,   0.18824f },
  {   0.79608f,   0.57255f,   0.25098f },
  {   0.90196f,   0.59608f,   0.35294f },
  {   0.96863f,   0.63137f,   0.47843f },
  {   0.99216f,   0.67059f,   0.60392f },
  {   0.99216f,   0.71373f,   0.72549f },
  {   0.98824f,   0.75686f,   0.85098f },
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
