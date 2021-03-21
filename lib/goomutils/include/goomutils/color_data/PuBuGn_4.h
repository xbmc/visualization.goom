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
static const std::vector<vivid::srgb_t> PuBuGn_4
{
  {   0.96471f,   0.93725f,   0.96863f },
  {   0.74118f,   0.78824f,   0.88235f },
  {   0.40392f,   0.66275f,   0.81176f },
  {   0.00784f,   0.50588f,   0.54118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
