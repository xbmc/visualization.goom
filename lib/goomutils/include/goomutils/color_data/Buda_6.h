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
static const std::vector<vivid::srgb_t> Buda_6
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.72157f,   0.25882f,   0.58039f },
  {   0.78039f,   0.43529f,   0.52157f },
  {   0.82745f,   0.60784f,   0.47451f },
  {   0.87059f,   0.78824f,   0.42745f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
