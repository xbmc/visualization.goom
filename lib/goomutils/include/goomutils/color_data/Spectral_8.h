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
static const std::vector<vivid::srgb_t> Spectral_8
{
  {   0.83529f,   0.24314f,   0.30980f },
  {   0.95686f,   0.42745f,   0.26275f },
  {   0.99216f,   0.68235f,   0.38039f },
  {   0.99608f,   0.87843f,   0.54510f },
  {   0.90196f,   0.96078f,   0.59608f },
  {   0.67059f,   0.86667f,   0.64314f },
  {   0.40000f,   0.76078f,   0.64706f },
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
