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
static const std::vector<vivid::srgb_t> Magma_5
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.31765f,   0.07059f,   0.48627f },
  {   0.71765f,   0.21569f,   0.47451f },
  {   0.98431f,   0.52941f,   0.38039f },
  {   0.98824f,   0.99216f,   0.74902f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
