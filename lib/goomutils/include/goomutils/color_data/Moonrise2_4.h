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
static const std::vector<vivid::srgb_t> Moonrise2_4
{
  {   0.40000f,   0.48627f,   0.45490f },
  {   0.70980f,   0.41569f,   0.15294f },
  {   0.76078f,   0.72941f,   0.48627f },
  {   0.12157f,   0.09804f,   0.09020f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
