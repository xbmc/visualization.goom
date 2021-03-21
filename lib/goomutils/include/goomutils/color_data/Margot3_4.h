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
static const std::vector<vivid::srgb_t> Margot3_4
{
  {   0.52941f,   0.63529f,   0.64314f },
  {   0.79216f,   0.62745f,   0.39608f },
  {   0.83922f,   0.79216f,   0.74902f },
  {   0.83922f,   0.62745f,   0.62745f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
