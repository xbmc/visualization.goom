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
static const std::vector<vivid::srgb_t> Thermal_12
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.05098f,   0.19216f,   0.39608f },
  {   0.20784f,   0.20000f,   0.61176f },
  {   0.37255f,   0.24706f,   0.60000f },
  {   0.49412f,   0.30588f,   0.56471f },
  {   0.62353f,   0.35294f,   0.53333f },
  {   0.75686f,   0.39216f,   0.47843f },
  {   0.88235f,   0.44706f,   0.38431f },
  {   0.96471f,   0.54118f,   0.27843f },
  {   0.98824f,   0.68235f,   0.23529f },
  {   0.96471f,   0.82745f,   0.27843f },
  {   0.90980f,   0.98039f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
