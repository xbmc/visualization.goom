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
static const std::vector<vivid::srgb_t> Viridis_10
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.28235f,   0.15686f,   0.47059f },
  {   0.24314f,   0.29020f,   0.53725f },
  {   0.19216f,   0.40784f,   0.55686f },
  {   0.14902f,   0.50980f,   0.55686f },
  {   0.12157f,   0.61961f,   0.53725f },
  {   0.20784f,   0.71765f,   0.47451f },
  {   0.42353f,   0.80392f,   0.35294f },
  {   0.70980f,   0.87059f,   0.16863f },
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
