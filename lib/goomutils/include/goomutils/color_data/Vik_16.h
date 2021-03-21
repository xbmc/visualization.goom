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
static const std::vector<vivid::srgb_t> Vik_16
{
  {   0.00000f,   0.07059f,   0.38039f },
  {   0.00784f,   0.17647f,   0.44706f },
  {   0.01176f,   0.27843f,   0.51373f },
  {   0.06667f,   0.39216f,   0.58824f },
  {   0.23529f,   0.52157f,   0.67451f },
  {   0.44314f,   0.65882f,   0.76863f },
  {   0.65490f,   0.78824f,   0.85490f },
  {   0.85882f,   0.89804f,   0.91373f },
  {   0.93333f,   0.85098f,   0.80392f },
  {   0.88235f,   0.72157f,   0.62745f },
  {   0.82745f,   0.59216f,   0.45490f },
  {   0.77647f,   0.47451f,   0.29804f },
  {   0.71765f,   0.35294f,   0.14902f },
  {   0.59608f,   0.20000f,   0.02745f },
  {   0.46275f,   0.09020f,   0.02353f },
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
