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
static const std::vector<vivid::srgb_t> Reds_9
{
  {   1.00000f,   0.96078f,   0.94118f },
  {   0.99608f,   0.87843f,   0.82353f },
  {   0.98824f,   0.73333f,   0.63137f },
  {   0.98824f,   0.57255f,   0.44706f },
  {   0.98431f,   0.41569f,   0.29020f },
  {   0.93725f,   0.23137f,   0.17255f },
  {   0.79608f,   0.09412f,   0.11373f },
  {   0.64706f,   0.05882f,   0.08235f },
  {   0.40392f,   0.00000f,   0.05098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
