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
static const std::vector<vivid::srgb_t> BlueDarkOrange18_12
{
  {   0.00000f,   0.40000f,   0.40000f },
  {   0.00000f,   0.80000f,   0.80000f },
  {   0.00000f,   1.00000f,   1.00000f },
  {   0.39608f,   1.00000f,   1.00000f },
  {   0.60000f,   1.00000f,   1.00000f },
  {   0.79608f,   1.00000f,   1.00000f },
  {   0.89804f,   1.00000f,   1.00000f },
  {   1.00000f,   0.79216f,   0.60000f },
  {   1.00000f,   0.67843f,   0.39608f },
  {   1.00000f,   0.43137f,   0.00000f },
  {   0.80000f,   0.33333f,   0.00000f },
  {   0.40000f,   0.15294f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
