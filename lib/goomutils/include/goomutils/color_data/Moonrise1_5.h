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
static const std::vector<vivid::srgb_t> Moonrise1_5
{
  {   0.44706f,   0.79216f,   0.86667f },
  {   0.94118f,   0.64706f,   0.69020f },
  {   0.54902f,   0.52157f,   0.21176f },
  {   0.76471f,   0.70588f,   0.46667f },
  {   0.98039f,   0.81569f,   0.38824f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
