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
static const std::vector<vivid::srgb_t> Oranges_5
{
  {   0.99608f,   0.92941f,   0.87059f },
  {   0.99216f,   0.74510f,   0.52157f },
  {   0.99216f,   0.55294f,   0.23529f },
  {   0.90196f,   0.33333f,   0.05098f },
  {   0.65098f,   0.21176f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
