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
static const std::vector<vivid::srgb_t> Ice_15
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.08235f,   0.08235f,   0.17255f },
  {   0.14510f,   0.13725f,   0.27843f },
  {   0.20000f,   0.19608f,   0.40000f },
  {   0.23529f,   0.25098f,   0.51765f },
  {   0.24706f,   0.32157f,   0.61961f },
  {   0.24314f,   0.40000f,   0.68235f },
  {   0.25882f,   0.48235f,   0.71765f },
  {   0.30196f,   0.55686f,   0.74510f },
  {   0.36078f,   0.63137f,   0.77255f },
  {   0.43137f,   0.70588f,   0.80000f },
  {   0.52549f,   0.78039f,   0.83137f },
  {   0.65882f,   0.85098f,   0.87059f },
  {   0.78824f,   0.91765f,   0.92941f },
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
