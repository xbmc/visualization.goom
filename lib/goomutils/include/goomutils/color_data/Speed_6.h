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
static const std::vector<vivid::srgb_t> Speed_6
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.84706f,   0.77255f,   0.37255f },
  {   0.55686f,   0.63529f,   0.04314f },
  {   0.19608f,   0.50196f,   0.12157f },
  {   0.06275f,   0.32941f,   0.17255f },
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
