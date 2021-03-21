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
static const std::vector<vivid::srgb_t> Viridis_20
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.28235f,   0.07843f,   0.40392f },
  {   0.28235f,   0.14902f,   0.46667f },
  {   0.27059f,   0.21569f,   0.50588f },
  {   0.24706f,   0.27843f,   0.53333f },
  {   0.22353f,   0.33333f,   0.54902f },
  {   0.19608f,   0.39216f,   0.55686f },
  {   0.17647f,   0.44314f,   0.55686f },
  {   0.15686f,   0.49020f,   0.55686f },
  {   0.13725f,   0.54118f,   0.55294f },
  {   0.12157f,   0.58824f,   0.54510f },
  {   0.12549f,   0.63922f,   0.52549f },
  {   0.16078f,   0.68627f,   0.49804f },
  {   0.23137f,   0.73333f,   0.45882f },
  {   0.33725f,   0.77647f,   0.40392f },
  {   0.45098f,   0.81569f,   0.33725f },
  {   0.58431f,   0.84706f,   0.25098f },
  {   0.72157f,   0.87059f,   0.16078f },
  {   0.86667f,   0.89020f,   0.09412f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
