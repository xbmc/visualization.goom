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
static const std::vector<vivid::srgb_t> LinearL_8
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.17647f,   0.09804f,   0.32941f },
  {   0.10588f,   0.25882f,   0.53333f },
  {   0.00000f,   0.46275f,   0.36078f },
  {   0.00000f,   0.64706f,   0.15294f },
  {   0.52941f,   0.76471f,   0.00000f },
  {   0.93333f,   0.83137f,   0.65882f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
