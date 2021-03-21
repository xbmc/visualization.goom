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
static const std::vector<vivid::srgb_t> Turku_11
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.13333f,   0.13333f,   0.12157f },
  {   0.23529f,   0.23529f,   0.19608f },
  {   0.33725f,   0.33725f,   0.25098f },
  {   0.44314f,   0.43922f,   0.29804f },
  {   0.57647f,   0.54902f,   0.35686f },
  {   0.72549f,   0.62745f,   0.43137f },
  {   0.84706f,   0.65490f,   0.50980f },
  {   0.93725f,   0.69412f,   0.63137f },
  {   0.99216f,   0.79608f,   0.78039f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
