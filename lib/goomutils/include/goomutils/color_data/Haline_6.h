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
static const std::vector<vivid::srgb_t> Haline_6
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.05098f,   0.30588f,   0.58824f },
  {   0.17647f,   0.48627f,   0.53725f },
  {   0.29020f,   0.66667f,   0.50588f },
  {   0.58039f,   0.82745f,   0.36471f },
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
