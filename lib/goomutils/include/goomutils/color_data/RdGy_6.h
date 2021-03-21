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
static const std::vector<vivid::srgb_t> RdGy_6
{
  {   0.69804f,   0.09412f,   0.16863f },
  {   0.93725f,   0.54118f,   0.38431f },
  {   0.99216f,   0.85882f,   0.78039f },
  {   0.87843f,   0.87843f,   0.87843f },
  {   0.60000f,   0.60000f,   0.60000f },
  {   0.30196f,   0.30196f,   0.30196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
