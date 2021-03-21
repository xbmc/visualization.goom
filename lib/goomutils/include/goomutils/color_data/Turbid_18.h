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
static const std::vector<vivid::srgb_t> Turbid_18
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.87843f,   0.89412f,   0.58431f },
  {   0.85098f,   0.82745f,   0.50196f },
  {   0.82353f,   0.76078f,   0.42745f },
  {   0.79608f,   0.69804f,   0.36078f },
  {   0.76863f,   0.63529f,   0.30588f },
  {   0.73725f,   0.57255f,   0.26667f },
  {   0.70196f,   0.51765f,   0.24706f },
  {   0.65882f,   0.46667f,   0.23529f },
  {   0.60784f,   0.41961f,   0.23137f },
  {   0.55294f,   0.37647f,   0.22745f },
  {   0.49412f,   0.33725f,   0.22353f },
  {   0.43529f,   0.29804f,   0.21176f },
  {   0.37255f,   0.26275f,   0.20000f },
  {   0.31373f,   0.23137f,   0.18039f },
  {   0.25098f,   0.19608f,   0.16078f },
  {   0.19216f,   0.15686f,   0.13333f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
