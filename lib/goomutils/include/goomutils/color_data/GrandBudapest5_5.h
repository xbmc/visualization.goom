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
static const std::vector<vivid::srgb_t> GrandBudapest5_5
{
  {   0.88235f,   0.57255f,   0.51373f },
  {   0.54902f,   0.10588f,   0.29804f },
  {   0.81961f,   0.57647f,   0.21176f },
  {   0.90588f,   0.78039f,   0.74510f },
  {   0.20000f,   0.04706f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
