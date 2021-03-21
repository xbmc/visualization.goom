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
static const std::vector<vivid::srgb_t> Delta_12
{
  {   0.06667f,   0.12549f,   0.25098f },
  {   0.14902f,   0.24314f,   0.56863f },
  {   0.12157f,   0.43529f,   0.63137f },
  {   0.23922f,   0.60784f,   0.67451f },
  {   0.54510f,   0.75686f,   0.72941f },
  {   0.85098f,   0.89804f,   0.85490f },
  {   0.93725f,   0.88627f,   0.61176f },
  {   0.76471f,   0.71765f,   0.23137f },
  {   0.45882f,   0.60000f,   0.02353f },
  {   0.14118f,   0.47451f,   0.14118f },
  {   0.07059f,   0.30980f,   0.16863f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
