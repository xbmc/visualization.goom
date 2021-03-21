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
static const std::vector<vivid::srgb_t> Broc_7
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.18824f,   0.36078f,   0.54902f },
  {   0.54510f,   0.65490f,   0.76078f },
  {   0.92157f,   0.93333f,   0.92549f },
  {   0.77255f,   0.77255f,   0.56078f },
  {   0.44706f,   0.44706f,   0.24706f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
