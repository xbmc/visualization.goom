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
static const std::vector<vivid::srgb_t> Delta_19
{
  {   0.06667f,   0.12549f,   0.25098f },
  {   0.13333f,   0.19608f,   0.43529f },
  {   0.12157f,   0.29020f,   0.60784f },
  {   0.10980f,   0.40392f,   0.62745f },
  {   0.16471f,   0.51373f,   0.65098f },
  {   0.25098f,   0.61961f,   0.67843f },
  {   0.42353f,   0.70980f,   0.70196f },
  {   0.63922f,   0.79216f,   0.76078f },
  {   0.81961f,   0.88235f,   0.83922f },
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.92549f,   0.86275f,   0.56863f },
  {   0.82745f,   0.75686f,   0.33333f },
  {   0.66667f,   0.67451f,   0.12549f },
  {   0.47843f,   0.60784f,   0.02353f },
  {   0.28235f,   0.53725f,   0.08627f },
  {   0.09412f,   0.45098f,   0.15686f },
  {   0.05098f,   0.34902f,   0.17647f },
  {   0.09412f,   0.24314f,   0.14510f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
