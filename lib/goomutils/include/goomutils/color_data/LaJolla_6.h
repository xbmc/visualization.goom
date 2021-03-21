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
static const std::vector<vivid::srgb_t> LaJolla_6
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.96471f,   0.83137f,   0.43922f },
  {   0.90588f,   0.58039f,   0.32157f },
  {   0.76078f,   0.33333f,   0.29020f },
  {   0.40784f,   0.20784f,   0.16471f },
  {   0.10196f,   0.10196f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
