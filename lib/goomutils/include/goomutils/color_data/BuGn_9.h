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
static const std::vector<vivid::srgb_t> BuGn_9
{
  {   0.96863f,   0.98824f,   0.99216f },
  {   0.89804f,   0.96078f,   0.97647f },
  {   0.80000f,   0.92549f,   0.90196f },
  {   0.60000f,   0.84706f,   0.78824f },
  {   0.40000f,   0.76078f,   0.64314f },
  {   0.25490f,   0.68235f,   0.46275f },
  {   0.13725f,   0.54510f,   0.27059f },
  {   0.00000f,   0.42745f,   0.17255f },
  {   0.00000f,   0.26667f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
