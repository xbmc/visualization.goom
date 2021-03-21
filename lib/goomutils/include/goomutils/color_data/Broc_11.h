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
static const std::vector<vivid::srgb_t> Broc_11
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.15686f,   0.25490f,   0.45490f },
  {   0.24706f,   0.41961f,   0.60000f },
  {   0.46275f,   0.59216f,   0.71765f },
  {   0.70196f,   0.77255f,   0.84314f },
  {   0.92157f,   0.93333f,   0.92549f },
  {   0.86275f,   0.85882f,   0.72157f },
  {   0.71373f,   0.71373f,   0.48627f },
  {   0.50588f,   0.50588f,   0.29804f },
  {   0.31373f,   0.31373f,   0.13725f },
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
