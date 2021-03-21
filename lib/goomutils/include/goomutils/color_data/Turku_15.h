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
static const std::vector<vivid::srgb_t> Turku_15
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.10196f,   0.10196f,   0.09412f },
  {   0.17255f,   0.17255f,   0.15294f },
  {   0.25098f,   0.25098f,   0.20392f },
  {   0.32549f,   0.32157f,   0.24314f },
  {   0.39608f,   0.39608f,   0.27843f },
  {   0.47451f,   0.46667f,   0.31373f },
  {   0.57647f,   0.54902f,   0.35686f },
  {   0.68627f,   0.61176f,   0.40784f },
  {   0.78431f,   0.64314f,   0.46667f },
  {   0.85882f,   0.65882f,   0.52549f },
  {   0.92549f,   0.68235f,   0.60784f },
  {   0.97647f,   0.74902f,   0.71765f },
  {   0.99608f,   0.82353f,   0.81569f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
