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
static const std::vector<vivid::srgb_t> Cork_16
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.19608f,   0.39608f },
  {   0.16863f,   0.29804f,   0.49412f },
  {   0.23922f,   0.40784f,   0.58824f },
  {   0.37255f,   0.52157f,   0.67059f },
  {   0.51765f,   0.63137f,   0.74510f },
  {   0.66667f,   0.74902f,   0.82745f },
  {   0.81176f,   0.86275f,   0.89412f },
  {   0.83922f,   0.90196f,   0.85882f },
  {   0.71765f,   0.83529f,   0.72941f },
  {   0.58431f,   0.75686f,   0.60000f },
  {   0.45098f,   0.67843f,   0.47059f },
  {   0.32549f,   0.58824f,   0.33333f },
  {   0.25490f,   0.47843f,   0.19216f },
  {   0.25490f,   0.38039f,   0.09412f },
  {   0.25882f,   0.30196f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
