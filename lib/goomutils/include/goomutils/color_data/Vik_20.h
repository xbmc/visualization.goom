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
static const std::vector<vivid::srgb_t> Vik_20
{
  {   0.00000f,   0.07059f,   0.38039f },
  {   0.00784f,   0.15294f,   0.43137f },
  {   0.01176f,   0.23529f,   0.48627f },
  {   0.01961f,   0.31765f,   0.53725f },
  {   0.09020f,   0.41176f,   0.60000f },
  {   0.22353f,   0.51373f,   0.67059f },
  {   0.39216f,   0.62745f,   0.74510f },
  {   0.55294f,   0.72941f,   0.81569f },
  {   0.71373f,   0.82745f,   0.88235f },
  {   0.87843f,   0.90196f,   0.91373f },
  {   0.93333f,   0.86667f,   0.82745f },
  {   0.89804f,   0.75686f,   0.67843f },
  {   0.85882f,   0.65882f,   0.54510f },
  {   0.81569f,   0.56471f,   0.41961f },
  {   0.77647f,   0.46667f,   0.29020f },
  {   0.73333f,   0.37647f,   0.17647f },
  {   0.64706f,   0.25098f,   0.05882f },
  {   0.53725f,   0.14902f,   0.02353f },
  {   0.43529f,   0.06667f,   0.02745f },
  {   0.34902f,   0.00000f,   0.03137f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
