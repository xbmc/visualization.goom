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
static const std::vector<vivid::srgb_t> GreenMagenta_6
{
  {   0.00000f,   0.31373f,   0.00000f },
  {   0.00000f,   0.94510f,   0.00000f },
  {   0.73333f,   1.00000f,   0.73333f },
  {   1.00000f,   0.73333f,   1.00000f },
  {   0.94510f,   0.00000f,   0.94510f },
  {   0.31373f,   0.00000f,   0.31373f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
