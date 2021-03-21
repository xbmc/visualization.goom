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
static const std::vector<vivid::srgb_t> Acton_6
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.40000f,   0.31373f,   0.48235f },
  {   0.65098f,   0.40000f,   0.58039f },
  {   0.83137f,   0.52549f,   0.67843f },
  {   0.83529f,   0.69804f,   0.80392f },
  {   0.90196f,   0.90196f,   0.94118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
