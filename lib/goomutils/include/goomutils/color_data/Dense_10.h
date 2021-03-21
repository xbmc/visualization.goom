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
static const std::vector<vivid::srgb_t> Dense_10
{
  {   0.90196f,   0.94510f,   0.94510f },
  {   0.71765f,   0.85490f,   0.89412f },
  {   0.55686f,   0.75294f,   0.88627f },
  {   0.46275f,   0.64314f,   0.89804f },
  {   0.45882f,   0.51373f,   0.87451f },
  {   0.47451f,   0.38039f,   0.78431f },
  {   0.46275f,   0.25882f,   0.64706f },
  {   0.41961f,   0.15686f,   0.47843f },
  {   0.33725f,   0.08627f,   0.29412f },
  {   0.21176f,   0.05490f,   0.14118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
