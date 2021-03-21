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
static const std::vector<vivid::srgb_t> Tokyo_6
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.40392f,   0.21569f,   0.38431f },
  {   0.54510f,   0.43529f,   0.49804f },
  {   0.58039f,   0.61961f,   0.54902f },
  {   0.68235f,   0.83922f,   0.63529f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
