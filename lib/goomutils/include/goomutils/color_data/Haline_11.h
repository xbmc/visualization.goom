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
static const std::vector<vivid::srgb_t> Haline_11
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.15686f,   0.16078f,   0.63922f },
  {   0.05098f,   0.30588f,   0.58824f },
  {   0.09412f,   0.40000f,   0.54902f },
  {   0.17647f,   0.48627f,   0.53725f },
  {   0.23529f,   0.57647f,   0.52941f },
  {   0.29020f,   0.66667f,   0.50588f },
  {   0.38824f,   0.75294f,   0.44706f },
  {   0.58039f,   0.82745f,   0.36471f },
  {   0.81569f,   0.87843f,   0.42745f },
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
