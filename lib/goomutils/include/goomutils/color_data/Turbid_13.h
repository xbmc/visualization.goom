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
static const std::vector<vivid::srgb_t> Turbid_13
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.86667f,   0.86667f,   0.55294f },
  {   0.82745f,   0.77647f,   0.44314f },
  {   0.79216f,   0.68235f,   0.34510f },
  {   0.74902f,   0.59216f,   0.27843f },
  {   0.69804f,   0.51373f,   0.24314f },
  {   0.63137f,   0.43922f,   0.23137f },
  {   0.55686f,   0.37647f,   0.22745f },
  {   0.47451f,   0.32549f,   0.21961f },
  {   0.38824f,   0.27451f,   0.20392f },
  {   0.30588f,   0.22353f,   0.18039f },
  {   0.21569f,   0.17255f,   0.14510f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
