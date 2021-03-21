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
static const std::vector<vivid::srgb_t> Algae_7
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.63529f,   0.83529f,   0.58431f },
  {   0.39216f,   0.70588f,   0.38824f },
  {   0.07059f,   0.58039f,   0.31373f },
  {   0.07059f,   0.43137f,   0.27059f },
  {   0.10196f,   0.28627f,   0.18824f },
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
