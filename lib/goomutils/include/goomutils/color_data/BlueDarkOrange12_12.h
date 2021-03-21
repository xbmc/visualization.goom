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
static const std::vector<vivid::srgb_t> BlueDarkOrange12_12
{
  {   0.11765f,   0.55686f,   0.60000f },
  {   0.31765f,   0.76471f,   0.80000f },
  {   0.60000f,   0.97647f,   1.00000f },
  {   0.69804f,   0.98824f,   1.00000f },
  {   0.80000f,   0.99608f,   1.00000f },
  {   0.89804f,   1.00000f,   1.00000f },
  {   1.00000f,   0.89804f,   0.80000f },
  {   1.00000f,   0.79216f,   0.60000f },
  {   1.00000f,   0.67843f,   0.39608f },
  {   1.00000f,   0.55686f,   0.19608f },
  {   0.80000f,   0.34510f,   0.00000f },
  {   0.60000f,   0.24706f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
