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
static const std::vector<vivid::srgb_t> CubeYF_12
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.52549f,   0.14118f,   0.77647f },
  {   0.47059f,   0.31373f,   0.94510f },
  {   0.40392f,   0.45098f,   0.99216f },
  {   0.32941f,   0.57647f,   0.89412f },
  {   0.24314f,   0.68627f,   0.76863f },
  {   0.24706f,   0.76078f,   0.62353f },
  {   0.29804f,   0.82745f,   0.45490f },
  {   0.35686f,   0.88627f,   0.30588f },
  {   0.51765f,   0.92157f,   0.31373f },
  {   0.69020f,   0.92549f,   0.34118f },
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
