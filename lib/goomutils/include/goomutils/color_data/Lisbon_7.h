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
static const std::vector<vivid::srgb_t> Lisbon_7
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.46667f,   0.58039f,   0.74118f },
  {   0.11765f,   0.26275f,   0.40784f },
  {   0.09020f,   0.09804f,   0.09804f },
  {   0.34118f,   0.31765f,   0.20392f },
  {   0.67059f,   0.63529f,   0.43137f },
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
