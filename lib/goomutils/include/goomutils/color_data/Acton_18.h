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
static const std::vector<vivid::srgb_t> Acton_18
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.23922f,   0.18431f,   0.35294f },
  {   0.30196f,   0.23922f,   0.40784f },
  {   0.37255f,   0.29020f,   0.46275f },
  {   0.44706f,   0.34118f,   0.51373f },
  {   0.52549f,   0.37647f,   0.54902f },
  {   0.59608f,   0.39216f,   0.56863f },
  {   0.66275f,   0.40000f,   0.58039f },
  {   0.72941f,   0.41176f,   0.59216f },
  {   0.79608f,   0.45490f,   0.62745f },
  {   0.83137f,   0.51373f,   0.67059f },
  {   0.83137f,   0.56863f,   0.70980f },
  {   0.82745f,   0.61569f,   0.74118f },
  {   0.83137f,   0.66667f,   0.78039f },
  {   0.83922f,   0.72157f,   0.81569f },
  {   0.85490f,   0.78039f,   0.85882f },
  {   0.87843f,   0.83922f,   0.89804f },
  {   0.90196f,   0.90196f,   0.94118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
