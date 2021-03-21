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
static const std::vector<vivid::srgb_t> IsleOfDogs2_6
{
  {   0.59608f,   0.42353f,   0.58824f },
  {   0.54118f,   0.12157f,   0.12157f },
  {   0.83529f,   0.67059f,   0.33333f },
  {   0.05490f,   0.04706f,   0.04706f },
  {   0.86275f,   0.76078f,   0.78824f },
  {   0.50980f,   0.44706f,   0.42353f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
