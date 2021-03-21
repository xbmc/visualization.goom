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
static const std::vector<vivid::srgb_t> Vivid_5
{
  {   0.89804f,   0.52549f,   0.02353f },
  {   0.36471f,   0.41176f,   0.69412f },
  {   0.32157f,   0.73725f,   0.63922f },
  {   0.60000f,   0.78824f,   0.27059f },
  {   0.80000f,   0.38039f,   0.69020f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
