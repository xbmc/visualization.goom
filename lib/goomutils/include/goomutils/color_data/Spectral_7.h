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
static const std::vector<vivid::srgb_t> Spectral_7
{
  {   0.83529f,   0.24314f,   0.30980f },
  {   0.98824f,   0.55294f,   0.34902f },
  {   0.99608f,   0.87843f,   0.54510f },
  {   1.00000f,   1.00000f,   0.74902f },
  {   0.90196f,   0.96078f,   0.59608f },
  {   0.60000f,   0.83529f,   0.58039f },
  {   0.19608f,   0.53333f,   0.74118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
