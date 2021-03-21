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
static const std::vector<vivid::srgb_t> Delta_15
{
  {   0.06667f,   0.12549f,   0.25098f },
  {   0.14510f,   0.21569f,   0.49412f },
  {   0.10588f,   0.35686f,   0.61961f },
  {   0.15294f,   0.50196f,   0.64706f },
  {   0.26667f,   0.63137f,   0.68235f },
  {   0.51765f,   0.74510f,   0.72157f },
  {   0.77255f,   0.85490f,   0.81569f },
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.90196f,   0.83137f,   0.50196f },
  {   0.74510f,   0.70588f,   0.21176f },
  {   0.50588f,   0.61569f,   0.02353f },
  {   0.24706f,   0.52157f,   0.10196f },
  {   0.05098f,   0.40784f,   0.16863f },
  {   0.08627f,   0.27451f,   0.16078f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
