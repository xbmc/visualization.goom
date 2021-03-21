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
static const std::vector<vivid::srgb_t> Algae_16
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.76078f,   0.91765f,   0.71765f },
  {   0.67451f,   0.85882f,   0.62745f },
  {   0.58824f,   0.80392f,   0.54118f },
  {   0.49412f,   0.75686f,   0.45882f },
  {   0.39216f,   0.70588f,   0.38824f },
  {   0.26667f,   0.65882f,   0.33333f },
  {   0.12549f,   0.61176f,   0.31765f },
  {   0.03529f,   0.55294f,   0.30980f },
  {   0.03529f,   0.49020f,   0.29412f },
  {   0.07059f,   0.43137f,   0.27059f },
  {   0.09020f,   0.37255f,   0.23922f },
  {   0.10196f,   0.31373f,   0.20392f },
  {   0.09804f,   0.25490f,   0.16863f },
  {   0.09020f,   0.20000f,   0.12549f },
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
