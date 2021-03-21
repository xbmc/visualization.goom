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
static const std::vector<vivid::srgb_t> LinearL_16
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.14510f,   0.05882f,   0.12549f },
  {   0.17647f,   0.09412f,   0.30196f },
  {   0.15686f,   0.14902f,   0.47059f },
  {   0.10588f,   0.23922f,   0.51373f },
  {   0.03922f,   0.33333f,   0.47843f },
  {   0.00000f,   0.42353f,   0.39608f },
  {   0.00000f,   0.51373f,   0.30196f },
  {   0.00000f,   0.60000f,   0.20784f },
  {   0.07843f,   0.67059f,   0.00000f },
  {   0.30980f,   0.73725f,   0.00000f },
  {   0.61569f,   0.77255f,   0.00000f },
  {   0.81961f,   0.79608f,   0.34118f },
  {   0.95294f,   0.83529f,   0.68627f },
  {   0.97255f,   0.91765f,   0.87843f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
