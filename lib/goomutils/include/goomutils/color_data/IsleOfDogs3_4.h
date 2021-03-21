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
static const std::vector<vivid::srgb_t> IsleOfDogs3_4
{
  {   0.89804f,   0.55686f,   0.65490f },
  {   0.87843f,   0.75686f,   0.62745f },
  {   0.11765f,   0.07059f,   0.38824f },
  {   0.84706f,   0.69412f,   0.28235f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
