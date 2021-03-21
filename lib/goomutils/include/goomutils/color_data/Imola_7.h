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
static const std::vector<vivid::srgb_t> Imola_7
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.16078f,   0.31373f,   0.64314f },
  {   0.22353f,   0.41961f,   0.58039f },
  {   0.32941f,   0.52549f,   0.49804f },
  {   0.48235f,   0.68235f,   0.45490f },
  {   0.66667f,   0.85490f,   0.41176f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
