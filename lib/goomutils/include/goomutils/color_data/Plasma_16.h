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
static const std::vector<vivid::srgb_t> Plasma_16
{
  {   0.05098f,   0.03137f,   0.52941f },
  {   0.20000f,   0.01961f,   0.59216f },
  {   0.31373f,   0.00784f,   0.63529f },
  {   0.41569f,   0.00000f,   0.65882f },
  {   0.51765f,   0.01961f,   0.65490f },
  {   0.61176f,   0.09020f,   0.61961f },
  {   0.69412f,   0.16471f,   0.56471f },
  {   0.76471f,   0.23922f,   0.50196f },
  {   0.82745f,   0.31765f,   0.44314f },
  {   0.88235f,   0.39216f,   0.38431f },
  {   0.92941f,   0.47451f,   0.32549f },
  {   0.96471f,   0.56078f,   0.26667f },
  {   0.98824f,   0.65098f,   0.21176f },
  {   0.99608f,   0.75294f,   0.16078f },
  {   0.97647f,   0.86275f,   0.14118f },
  {   0.94118f,   0.97647f,   0.12941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
