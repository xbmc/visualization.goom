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
static const std::vector<vivid::srgb_t> Nuuk_11
{
  {   0.01961f,   0.34902f,   0.54902f },
  {   0.15294f,   0.38039f,   0.51765f },
  {   0.26275f,   0.43137f,   0.50980f },
  {   0.38824f,   0.50196f,   0.53725f },
  {   0.52157f,   0.58039f,   0.57647f },
  {   0.63137f,   0.65098f,   0.59608f },
  {   0.69804f,   0.69804f,   0.57647f },
  {   0.74118f,   0.74118f,   0.54118f },
  {   0.79216f,   0.79216f,   0.51373f },
  {   0.89412f,   0.89020f,   0.56863f },
  {   0.99608f,   0.99608f,   0.69804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
