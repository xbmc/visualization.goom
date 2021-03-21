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
static const std::vector<vivid::srgb_t> Geyser_7
{
  {   0.00000f,   0.50196f,   0.50196f },
  {   0.43922f,   0.64314f,   0.58039f },
  {   0.70588f,   0.78431f,   0.65882f },
  {   0.96471f,   0.92941f,   0.74118f },
  {   0.92941f,   0.73333f,   0.54118f },
  {   0.87059f,   0.54118f,   0.35294f },
  {   0.79216f,   0.33725f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
