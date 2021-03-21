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
static const std::vector<vivid::srgb_t> Mendl_4
{
  {   0.87059f,   0.55294f,   0.72549f },
  {   0.72157f,   0.75294f,   0.96471f },
  {   0.81176f,   0.57647f,   0.52941f },
  {   0.36078f,   0.50196f,   0.80000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
