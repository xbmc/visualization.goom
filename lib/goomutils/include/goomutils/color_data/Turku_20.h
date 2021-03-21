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
static const std::vector<vivid::srgb_t> Turku_20
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.08235f,   0.08235f,   0.07451f },
  {   0.13725f,   0.13725f,   0.12157f },
  {   0.18824f,   0.18824f,   0.16471f },
  {   0.24706f,   0.24706f,   0.20392f },
  {   0.30196f,   0.29804f,   0.23137f },
  {   0.35686f,   0.35686f,   0.25882f },
  {   0.40784f,   0.40784f,   0.28235f },
  {   0.46667f,   0.45882f,   0.30980f },
  {   0.53725f,   0.51765f,   0.33725f },
  {   0.61176f,   0.57255f,   0.37255f },
  {   0.69804f,   0.61569f,   0.41569f },
  {   0.76863f,   0.64314f,   0.45490f },
  {   0.82745f,   0.65098f,   0.49804f },
  {   0.88235f,   0.66275f,   0.54902f },
  {   0.92941f,   0.68627f,   0.61176f },
  {   0.96863f,   0.73333f,   0.69412f },
  {   0.98824f,   0.78431f,   0.76863f },
  {   1.00000f,   0.84706f,   0.83922f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
