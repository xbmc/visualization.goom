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
static const std::vector<vivid::srgb_t> Ice_8
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.14510f,   0.13725f,   0.27843f },
  {   0.23529f,   0.25098f,   0.51765f },
  {   0.24314f,   0.40000f,   0.68235f },
  {   0.30196f,   0.55686f,   0.74510f },
  {   0.43137f,   0.70588f,   0.80000f },
  {   0.65882f,   0.85098f,   0.87059f },
  {   0.91765f,   0.99216f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
