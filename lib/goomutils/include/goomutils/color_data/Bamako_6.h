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
static const std::vector<vivid::srgb_t> Bamako_6
{
  {   0.00000f,   0.25098f,   0.29804f },
  {   0.13333f,   0.33333f,   0.22353f },
  {   0.28235f,   0.43137f,   0.13333f },
  {   0.50196f,   0.55294f,   0.01569f },
  {   0.80392f,   0.70980f,   0.23922f },
  {   1.00000f,   0.89804f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
