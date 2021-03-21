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
static const std::vector<vivid::srgb_t> Tokyo_16
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.20392f,   0.09412f,   0.25882f },
  {   0.30588f,   0.14510f,   0.32157f },
  {   0.40392f,   0.21569f,   0.38431f },
  {   0.47843f,   0.29412f,   0.43529f },
  {   0.52157f,   0.36863f,   0.47059f },
  {   0.54510f,   0.43529f,   0.49804f },
  {   0.55686f,   0.49804f,   0.51765f },
  {   0.56863f,   0.55686f,   0.53333f },
  {   0.58039f,   0.61961f,   0.54902f },
  {   0.59216f,   0.68235f,   0.56863f },
  {   0.61961f,   0.75294f,   0.59216f },
  {   0.68235f,   0.83922f,   0.63529f },
  {   0.79216f,   0.92549f,   0.70980f },
  {   0.90588f,   0.97647f,   0.78431f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
