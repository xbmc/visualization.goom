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
static const std::vector<vivid::srgb_t> Broc_12
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16078f,   0.23529f,   0.43529f },
  {   0.21176f,   0.38824f,   0.57255f },
  {   0.40784f,   0.54902f,   0.69020f },
  {   0.61961f,   0.70980f,   0.80000f },
  {   0.83529f,   0.87451f,   0.90980f },
  {   0.92157f,   0.92157f,   0.85098f },
  {   0.81569f,   0.81569f,   0.63529f },
  {   0.65882f,   0.65882f,   0.42745f },
  {   0.46667f,   0.46667f,   0.26667f },
  {   0.29804f,   0.29804f,   0.12549f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
