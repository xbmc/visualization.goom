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
static const std::vector<vivid::srgb_t> Cork_20
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16863f,   0.17255f,   0.37255f },
  {   0.16471f,   0.25490f,   0.45490f },
  {   0.18431f,   0.33725f,   0.52941f },
  {   0.26275f,   0.42745f,   0.60392f },
  {   0.36471f,   0.51373f,   0.66275f },
  {   0.48235f,   0.60784f,   0.72941f },
  {   0.59608f,   0.69412f,   0.78824f },
  {   0.71373f,   0.78039f,   0.84706f },
  {   0.82745f,   0.87451f,   0.89804f },
  {   0.85098f,   0.90588f,   0.87059f },
  {   0.75686f,   0.85882f,   0.76863f },
  {   0.65490f,   0.79608f,   0.66667f },
  {   0.55294f,   0.73725f,   0.56863f },
  {   0.44314f,   0.67451f,   0.46275f },
  {   0.34510f,   0.60784f,   0.35686f },
  {   0.27059f,   0.51765f,   0.23922f },
  {   0.25098f,   0.43529f,   0.14902f },
  {   0.25882f,   0.36078f,   0.07451f },
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
