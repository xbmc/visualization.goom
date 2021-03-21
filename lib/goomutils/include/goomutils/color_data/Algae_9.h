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
static const std::vector<vivid::srgb_t> Algae_9
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.68627f,   0.86667f,   0.63529f },
  {   0.51765f,   0.76863f,   0.47843f },
  {   0.31373f,   0.67843f,   0.34902f },
  {   0.07059f,   0.58039f,   0.31373f },
  {   0.04706f,   0.47059f,   0.28627f },
  {   0.09412f,   0.35686f,   0.23137f },
  {   0.09804f,   0.25098f,   0.16078f },
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
