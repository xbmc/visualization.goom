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
static const std::vector<vivid::srgb_t> Viridis_16
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.28235f,   0.10196f,   0.42353f },
  {   0.27843f,   0.18431f,   0.49020f },
  {   0.25490f,   0.26667f,   0.52941f },
  {   0.22353f,   0.33725f,   0.54902f },
  {   0.19216f,   0.40784f,   0.55686f },
  {   0.16471f,   0.47059f,   0.55686f },
  {   0.13725f,   0.53333f,   0.55686f },
  {   0.12157f,   0.59608f,   0.54510f },
  {   0.13333f,   0.65882f,   0.51765f },
  {   0.20784f,   0.71765f,   0.47451f },
  {   0.32941f,   0.77255f,   0.40784f },
  {   0.47843f,   0.81961f,   0.31765f },
  {   0.64706f,   0.85882f,   0.21176f },
  {   0.82353f,   0.88627f,   0.10588f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
