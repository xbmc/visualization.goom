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
static const std::vector<vivid::srgb_t> Broc_10
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.15686f,   0.26667f,   0.46667f },
  {   0.29412f,   0.46275f,   0.62745f },
  {   0.54510f,   0.65490f,   0.76078f },
  {   0.80784f,   0.85098f,   0.89804f },
  {   0.90980f,   0.90980f,   0.82353f },
  {   0.77255f,   0.77255f,   0.56078f },
  {   0.55294f,   0.55294f,   0.33725f },
  {   0.33333f,   0.33333f,   0.15294f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
