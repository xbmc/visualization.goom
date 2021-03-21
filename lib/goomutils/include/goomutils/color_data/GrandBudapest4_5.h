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
static const std::vector<vivid::srgb_t> GrandBudapest4_5
{
  {   0.72941f,   0.43137f,   0.00000f },
  {   0.31373f,   0.12549f,   0.33725f },
  {   1.00000f,   0.96471f,   0.73333f },
  {   0.60392f,   0.49804f,   0.09804f },
  {   0.12157f,   0.07059f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
