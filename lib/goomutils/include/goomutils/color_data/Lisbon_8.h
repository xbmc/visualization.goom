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
static const std::vector<vivid::srgb_t> Lisbon_8
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.52549f,   0.62745f,   0.77647f },
  {   0.18431f,   0.34902f,   0.51765f },
  {   0.06667f,   0.13333f,   0.20000f },
  {   0.17647f,   0.16863f,   0.10980f },
  {   0.42745f,   0.40392f,   0.25490f },
  {   0.72549f,   0.69412f,   0.49020f },
  {   1.00000f,   1.00000f,   0.85098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
