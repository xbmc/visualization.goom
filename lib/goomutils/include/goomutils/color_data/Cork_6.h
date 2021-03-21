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
static const std::vector<vivid::srgb_t> Cork_6
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.23922f,   0.40784f,   0.58824f },
  {   0.66667f,   0.74902f,   0.82745f },
  {   0.71765f,   0.83529f,   0.72941f },
  {   0.32549f,   0.58824f,   0.33333f },
  {   0.25882f,   0.30196f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
