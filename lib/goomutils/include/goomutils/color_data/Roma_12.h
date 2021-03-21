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
static const std::vector<vivid::srgb_t> Roma_12
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.59608f,   0.30980f,   0.07843f },
  {   0.68235f,   0.48627f,   0.15294f },
  {   0.78431f,   0.68627f,   0.27843f },
  {   0.87843f,   0.86275f,   0.51373f },
  {   0.86275f,   0.92157f,   0.71765f },
  {   0.69412f,   0.90196f,   0.82745f },
  {   0.44706f,   0.79608f,   0.83922f },
  {   0.30196f,   0.63922f,   0.78824f },
  {   0.23137f,   0.47843f,   0.72157f },
  {   0.17255f,   0.33725f,   0.65882f },
  {   0.10196f,   0.20000f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
