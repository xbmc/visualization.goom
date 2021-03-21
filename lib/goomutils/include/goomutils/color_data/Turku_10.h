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
static const std::vector<vivid::srgb_t> Turku_10
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.14118f,   0.14118f,   0.12549f },
  {   0.25882f,   0.25882f,   0.20784f },
  {   0.37255f,   0.37255f,   0.26667f },
  {   0.49412f,   0.48627f,   0.32157f },
  {   0.66275f,   0.60000f,   0.39608f },
  {   0.81176f,   0.65098f,   0.48627f },
  {   0.91765f,   0.67843f,   0.59608f },
  {   0.98824f,   0.78039f,   0.76471f },
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
