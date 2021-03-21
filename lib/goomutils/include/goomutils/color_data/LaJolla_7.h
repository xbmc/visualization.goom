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
static const std::vector<vivid::srgb_t> LaJolla_7
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.97255f,   0.87451f,   0.50196f },
  {   0.92549f,   0.65882f,   0.33333f },
  {   0.87059f,   0.45490f,   0.30980f },
  {   0.64706f,   0.27843f,   0.25882f },
  {   0.35686f,   0.18824f,   0.14118f },
  {   0.10196f,   0.10196f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
