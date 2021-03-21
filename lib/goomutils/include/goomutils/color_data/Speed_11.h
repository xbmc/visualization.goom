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
static const std::vector<vivid::srgb_t> Speed_11
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.92941f,   0.87059f,   0.58824f },
  {   0.84706f,   0.77255f,   0.37255f },
  {   0.72157f,   0.69804f,   0.18431f },
  {   0.55686f,   0.63529f,   0.04314f },
  {   0.37255f,   0.57255f,   0.04706f },
  {   0.19608f,   0.50196f,   0.12157f },
  {   0.05882f,   0.42353f,   0.16863f },
  {   0.06275f,   0.32941f,   0.17255f },
  {   0.09804f,   0.23137f,   0.13725f },
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
