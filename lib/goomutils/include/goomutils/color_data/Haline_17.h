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
static const std::vector<vivid::srgb_t> Haline_17
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.18039f,   0.11373f,   0.57647f },
  {   0.12549f,   0.20392f,   0.63529f },
  {   0.05882f,   0.29020f,   0.59608f },
  {   0.05882f,   0.35686f,   0.56471f },
  {   0.10980f,   0.41569f,   0.54902f },
  {   0.16078f,   0.46667f,   0.53725f },
  {   0.20000f,   0.52157f,   0.53333f },
  {   0.23529f,   0.57647f,   0.52941f },
  {   0.26667f,   0.63137f,   0.51765f },
  {   0.30980f,   0.68627f,   0.49412f },
  {   0.37255f,   0.74510f,   0.45882f },
  {   0.47059f,   0.79608f,   0.40784f },
  {   0.60784f,   0.83529f,   0.36078f },
  {   0.75686f,   0.86667f,   0.39216f },
  {   0.88235f,   0.89804f,   0.48627f },
  {   0.99216f,   0.93725f,   0.60392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
