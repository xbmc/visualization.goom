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
static const std::vector<vivid::srgb_t> IsleOfDogs1_5
{
  {   0.99608f,   0.77255f,   0.68627f },
  {   0.68235f,   0.49412f,   0.44314f },
  {   0.82353f,   0.40392f,   0.19608f },
  {   0.19608f,   0.13725f,   0.13725f },
  {   0.09412f,   0.07059f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
