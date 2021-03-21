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
static const std::vector<vivid::srgb_t> Viridis_17
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.28235f,   0.09412f,   0.41569f },
  {   0.27843f,   0.17647f,   0.48235f },
  {   0.25882f,   0.25098f,   0.52549f },
  {   0.23137f,   0.32157f,   0.54510f },
  {   0.20000f,   0.38824f,   0.55294f },
  {   0.17255f,   0.44706f,   0.55686f },
  {   0.14902f,   0.50980f,   0.55686f },
  {   0.12941f,   0.56863f,   0.54902f },
  {   0.12157f,   0.62353f,   0.53333f },
  {   0.15294f,   0.67843f,   0.50588f },
  {   0.23922f,   0.73725f,   0.45490f },
  {   0.36078f,   0.78431f,   0.38824f },
  {   0.50588f,   0.82745f,   0.30196f },
  {   0.66667f,   0.86275f,   0.19608f },
  {   0.83529f,   0.88627f,   0.10196f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
