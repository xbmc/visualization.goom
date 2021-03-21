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
static const std::vector<vivid::srgb_t> Peach_6
{
  {   0.99216f,   0.87843f,   0.77255f },
  {   0.98039f,   0.79608f,   0.65098f },
  {   0.97255f,   0.70980f,   0.54510f },
  {   0.94902f,   0.52157f,   0.36471f },
  {   0.93725f,   0.41569f,   0.29804f },
  {   0.92157f,   0.29020f,   0.25098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
