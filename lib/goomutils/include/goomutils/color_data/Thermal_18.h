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
static const std::vector<vivid::srgb_t> Thermal_18
{
  {   0.01569f,   0.13725f,   0.20000f },
  {   0.03137f,   0.17647f,   0.32157f },
  {   0.08627f,   0.20000f,   0.46667f },
  {   0.20000f,   0.20000f,   0.60784f },
  {   0.31373f,   0.22353f,   0.61961f },
  {   0.40000f,   0.26275f,   0.59216f },
  {   0.47843f,   0.29804f,   0.56863f },
  {   0.56078f,   0.32941f,   0.54902f },
  {   0.64706f,   0.36078f,   0.52549f },
  {   0.73333f,   0.38431f,   0.49020f },
  {   0.81961f,   0.41569f,   0.43529f },
  {   0.89804f,   0.45490f,   0.36863f },
  {   0.95294f,   0.51373f,   0.29804f },
  {   0.98039f,   0.59608f,   0.24706f },
  {   0.98824f,   0.68627f,   0.23529f },
  {   0.97647f,   0.78431f,   0.25882f },
  {   0.94902f,   0.88235f,   0.30196f },
  {   0.90980f,   0.98039f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
