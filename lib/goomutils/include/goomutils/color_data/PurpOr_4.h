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
static const std::vector<vivid::srgb_t> PurpOr_4
{
  {   0.97647f,   0.86667f,   0.85490f },
  {   0.89804f,   0.59216f,   0.72549f },
  {   0.67843f,   0.37255f,   0.67843f },
  {   0.34118f,   0.23137f,   0.53333f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
