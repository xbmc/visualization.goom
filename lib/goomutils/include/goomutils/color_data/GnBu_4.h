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
static const std::vector<vivid::srgb_t> GnBu_4
{
  {   0.94118f,   0.97647f,   0.90980f },
  {   0.72941f,   0.89412f,   0.73725f },
  {   0.48235f,   0.80000f,   0.76863f },
  {   0.16863f,   0.54902f,   0.74510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
