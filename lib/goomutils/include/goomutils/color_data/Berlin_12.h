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
static const std::vector<vivid::srgb_t> Berlin_12
{
  {   0.61961f,   0.69020f,   1.00000f },
  {   0.40392f,   0.65882f,   0.89020f },
  {   0.21961f,   0.53725f,   0.69804f },
  {   0.14118f,   0.36471f,   0.47059f },
  {   0.08235f,   0.20784f,   0.26667f },
  {   0.06667f,   0.08235f,   0.09804f },
  {   0.14510f,   0.04706f,   0.00392f },
  {   0.26667f,   0.07451f,   0.00392f },
  {   0.43137f,   0.15686f,   0.07451f },
  {   0.62745f,   0.32549f,   0.25490f },
  {   0.80784f,   0.49804f,   0.46275f },
  {   1.00000f,   0.67843f,   0.67843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
