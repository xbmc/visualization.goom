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
static const std::vector<vivid::srgb_t> Algae_6
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.58824f,   0.80392f,   0.54118f },
  {   0.26667f,   0.65882f,   0.33333f },
  {   0.03529f,   0.49020f,   0.29412f },
  {   0.10196f,   0.31373f,   0.20392f },
  {   0.07059f,   0.14118f,   0.07843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
