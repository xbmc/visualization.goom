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
static const std::vector<vivid::srgb_t> Cork_11
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.24706f,   0.44706f },
  {   0.23922f,   0.40784f,   0.58824f },
  {   0.43922f,   0.57255f,   0.70588f },
  {   0.66667f,   0.74902f,   0.82745f },
  {   0.85882f,   0.90196f,   0.89804f },
  {   0.71765f,   0.83529f,   0.72941f },
  {   0.52157f,   0.71765f,   0.53725f },
  {   0.32549f,   0.58824f,   0.33333f },
  {   0.25098f,   0.42353f,   0.13725f },
  {   0.25882f,   0.30196f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
