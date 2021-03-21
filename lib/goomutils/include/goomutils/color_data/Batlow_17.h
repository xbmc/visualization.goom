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
static const std::vector<vivid::srgb_t> Batlow_17
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.03529f,   0.16471f,   0.36078f },
  {   0.05882f,   0.23137f,   0.37255f },
  {   0.08627f,   0.29804f,   0.38039f },
  {   0.13725f,   0.36078f,   0.37647f },
  {   0.21569f,   0.41176f,   0.34510f },
  {   0.30588f,   0.45098f,   0.29804f },
  {   0.40000f,   0.47843f,   0.24706f },
  {   0.50588f,   0.50980f,   0.20000f },
  {   0.61569f,   0.53725f,   0.18039f },
  {   0.74902f,   0.56471f,   0.21961f },
  {   0.87059f,   0.58824f,   0.31765f },
  {   0.95686f,   0.61961f,   0.44314f },
  {   0.98824f,   0.66275f,   0.58039f },
  {   0.99216f,   0.70588f,   0.70980f },
  {   0.98824f,   0.75294f,   0.84314f },
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
