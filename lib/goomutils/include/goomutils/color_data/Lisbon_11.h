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
static const std::vector<vivid::srgb_t> Lisbon_11
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.62745f,   0.70196f,   0.83922f },
  {   0.37647f,   0.51373f,   0.68235f },
  {   0.16471f,   0.32549f,   0.49020f },
  {   0.07451f,   0.16471f,   0.25882f },
  {   0.09020f,   0.09804f,   0.09804f },
  {   0.21961f,   0.20784f,   0.13333f },
  {   0.40000f,   0.37647f,   0.23922f },
  {   0.60392f,   0.56863f,   0.37647f },
  {   0.81176f,   0.78824f,   0.59608f },
  {   1.00000f,   1.00000f,   0.85098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
