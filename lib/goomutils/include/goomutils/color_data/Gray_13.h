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
static const std::vector<vivid::srgb_t> Gray_13
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.05882f,   0.05490f,   0.05490f },
  {   0.13725f,   0.13725f,   0.13725f },
  {   0.21569f,   0.21569f,   0.21569f },
  {   0.29020f,   0.29020f,   0.28627f },
  {   0.36471f,   0.36471f,   0.36078f },
  {   0.44706f,   0.44314f,   0.44314f },
  {   0.52549f,   0.52157f,   0.52157f },
  {   0.60784f,   0.60392f,   0.60392f },
  {   0.69412f,   0.69412f,   0.69020f },
  {   0.78824f,   0.78431f,   0.78039f },
  {   0.89020f,   0.89020f,   0.88627f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
