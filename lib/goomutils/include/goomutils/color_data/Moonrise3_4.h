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
static const std::vector<vivid::srgb_t> Moonrise3_4
{
  {   0.94902f,   0.85490f,   0.32157f },
  {   0.77255f,   0.61569f,   0.00000f },
  {   0.79608f,   0.79608f,   0.78824f },
  {   0.10588f,   0.11765f,   0.07843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
