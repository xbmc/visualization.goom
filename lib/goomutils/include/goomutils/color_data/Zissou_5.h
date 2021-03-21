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
static const std::vector<vivid::srgb_t> Zissou_5
{
  {   0.00000f,   0.60000f,   0.90196f },
  {   0.07059f,   0.14510f,   0.35294f },
  {   0.94902f,   0.21961f,   0.07843f },
  {   0.87451f,   0.71765f,   0.54510f },
  {   0.71373f,   0.76471f,   0.77255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
