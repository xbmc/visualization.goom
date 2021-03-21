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
static const std::vector<vivid::srgb_t> Moonrise5_6
{
  {   0.87451f,   0.54902f,   0.56471f },
  {   0.84706f,   0.82353f,   0.55686f },
  {   0.96078f,   0.74510f,   0.14510f },
  {   0.23922f,   0.29020f,   0.10980f },
  {   0.81961f,   0.18824f,   0.37647f },
  {   0.65882f,   0.41961f,   0.29804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
