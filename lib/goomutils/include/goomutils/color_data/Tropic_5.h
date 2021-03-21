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
static const std::vector<vivid::srgb_t> Tropic_5
{
  {   0.00000f,   0.60784f,   0.61961f },
  {   0.65490f,   0.82745f,   0.83137f },
  {   0.94510f,   0.94510f,   0.94510f },
  {   0.89412f,   0.75686f,   0.85098f },
  {   0.78039f,   0.36471f,   0.67059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
