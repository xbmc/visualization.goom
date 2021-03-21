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
static const std::vector<vivid::srgb_t> Sunset_6
{
  {   0.95294f,   0.90588f,   0.60784f },
  {   0.98039f,   0.76863f,   0.51765f },
  {   0.97255f,   0.62745f,   0.49412f },
  {   0.80784f,   0.40000f,   0.57647f },
  {   0.62745f,   0.34902f,   0.62745f },
  {   0.36078f,   0.32549f,   0.64706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
