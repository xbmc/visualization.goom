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
static const std::vector<vivid::srgb_t> CubeYF_20
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.52157f,   0.05098f,   0.69412f },
  {   0.52157f,   0.17647f,   0.80784f },
  {   0.49804f,   0.27059f,   0.90196f },
  {   0.44314f,   0.35686f,   0.98431f },
  {   0.40784f,   0.43137f,   1.00000f },
  {   0.36863f,   0.51765f,   0.94902f },
  {   0.32157f,   0.58039f,   0.89020f },
  {   0.27843f,   0.64314f,   0.82745f },
  {   0.22745f,   0.70588f,   0.74118f },
  {   0.23529f,   0.74902f,   0.65882f },
  {   0.27059f,   0.79216f,   0.55294f },
  {   0.29804f,   0.82745f,   0.46275f },
  {   0.32941f,   0.85882f,   0.37255f },
  {   0.36078f,   0.89020f,   0.28627f },
  {   0.44314f,   0.90980f,   0.29804f },
  {   0.56863f,   0.92157f,   0.32157f },
  {   0.67059f,   0.92549f,   0.33725f },
  {   0.74902f,   0.92549f,   0.34902f },
  {   0.81961f,   0.92157f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
