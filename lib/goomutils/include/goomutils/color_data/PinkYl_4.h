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
static const std::vector<vivid::srgb_t> PinkYl_4
{
  {   0.99608f,   0.96471f,   0.70980f },
  {   1.00000f,   0.76078f,   0.52157f },
  {   0.98039f,   0.54118f,   0.46275f },
  {   0.88235f,   0.32549f,   0.51373f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
