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
static const std::vector<vivid::srgb_t> CubeYF_19
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.52157f,   0.05882f,   0.70196f },
  {   0.51765f,   0.18431f,   0.81569f },
  {   0.49020f,   0.28235f,   0.91765f },
  {   0.43529f,   0.37255f,   0.98824f },
  {   0.40392f,   0.45490f,   0.99216f },
  {   0.35294f,   0.53725f,   0.93333f },
  {   0.30588f,   0.60392f,   0.86667f },
  {   0.25098f,   0.67451f,   0.78431f },
  {   0.22353f,   0.72941f,   0.69412f },
  {   0.25490f,   0.77255f,   0.60000f },
  {   0.28627f,   0.81569f,   0.50196f },
  {   0.31765f,   0.84706f,   0.40000f },
  {   0.35294f,   0.88235f,   0.30980f },
  {   0.42353f,   0.90588f,   0.29020f },
  {   0.54118f,   0.92157f,   0.31765f },
  {   0.65882f,   0.92549f,   0.33725f },
  {   0.74118f,   0.92549f,   0.34510f },
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
