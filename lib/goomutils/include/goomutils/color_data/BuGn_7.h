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
static const std::vector<vivid::srgb_t> BuGn_7
{
  {   0.92941f,   0.97255f,   0.98431f },
  {   0.80000f,   0.92549f,   0.90196f },
  {   0.60000f,   0.84706f,   0.78824f },
  {   0.40000f,   0.76078f,   0.64314f },
  {   0.25490f,   0.68235f,   0.46275f },
  {   0.13725f,   0.54510f,   0.27059f },
  {   0.00000f,   0.34510f,   0.14118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
