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
static const std::vector<vivid::srgb_t> Purp_4
{
  {   0.95294f,   0.87843f,   0.96863f },
  {   0.81961f,   0.68627f,   0.90980f },
  {   0.62353f,   0.50980f,   0.80784f },
  {   0.38824f,   0.34510f,   0.62353f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
