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
static const std::vector<vivid::srgb_t> Blues10_7
{
  {   0.89804f,   1.00000f,   1.00000f },
  {   0.69804f,   0.94902f,   1.00000f },
  {   0.60000f,   0.89804f,   1.00000f },
  {   0.49804f,   0.83137f,   1.00000f },
  {   0.29804f,   0.64706f,   1.00000f },
  {   0.09804f,   0.39608f,   1.00000f },
  {   0.00000f,   0.24706f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
