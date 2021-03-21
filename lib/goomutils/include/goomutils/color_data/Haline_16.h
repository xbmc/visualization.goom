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
static const std::vector<vivid::srgb_t> Haline_16
{
  {   0.16471f,   0.09412f,   0.42353f },
  {   0.18039f,   0.11765f,   0.58431f },
  {   0.11373f,   0.21569f,   0.63137f },
  {   0.05098f,   0.30588f,   0.58824f },
  {   0.07059f,   0.37255f,   0.56078f },
  {   0.12549f,   0.43137f,   0.54510f },
  {   0.17647f,   0.48627f,   0.53725f },
  {   0.21569f,   0.54510f,   0.53333f },
  {   0.25098f,   0.60392f,   0.52549f },
  {   0.29020f,   0.66667f,   0.50588f },
  {   0.35294f,   0.72549f,   0.47059f },
  {   0.44314f,   0.78431f,   0.41961f },
  {   0.58039f,   0.82745f,   0.36471f },
  {   0.74118f,   0.86275f,   0.38431f },
  {   0.87843f,   0.89804f,   0.47843f },
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
