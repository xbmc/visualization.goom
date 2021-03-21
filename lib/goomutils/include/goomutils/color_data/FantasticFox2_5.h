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
static const std::vector<vivid::srgb_t> FantasticFox2_5
{
  {   0.89412f,   0.74902f,   0.26667f },
  {   0.77647f,   0.34118f,   0.25882f },
  {   0.60392f,   0.81569f,   0.73333f },
  {   0.20000f,   0.15294f,   0.21569f },
  {   0.67059f,   0.63137f,   0.55294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
