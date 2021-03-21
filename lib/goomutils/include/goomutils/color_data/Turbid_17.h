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
static const std::vector<vivid::srgb_t> Turbid_17
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.87843f,   0.89020f,   0.58039f },
  {   0.84706f,   0.81961f,   0.49412f },
  {   0.81961f,   0.74902f,   0.41176f },
  {   0.79216f,   0.68235f,   0.34510f },
  {   0.76078f,   0.61176f,   0.29020f },
  {   0.72549f,   0.54902f,   0.25882f },
  {   0.68235f,   0.49020f,   0.23922f },
  {   0.63137f,   0.43922f,   0.23137f },
  {   0.58039f,   0.39608f,   0.22745f },
  {   0.51765f,   0.35294f,   0.22353f },
  {   0.45490f,   0.30980f,   0.21569f },
  {   0.38824f,   0.27451f,   0.20392f },
  {   0.32549f,   0.23529f,   0.18431f },
  {   0.25882f,   0.20000f,   0.16078f },
  {   0.19608f,   0.16078f,   0.13725f },
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
