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
static const std::vector<vivid::srgb_t> Gray_11
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.07843f,   0.07451f,   0.07451f },
  {   0.16863f,   0.16863f,   0.16863f },
  {   0.25882f,   0.25882f,   0.25490f },
  {   0.35294f,   0.34902f,   0.34902f },
  {   0.44706f,   0.44314f,   0.44314f },
  {   0.54118f,   0.53725f,   0.53725f },
  {   0.63922f,   0.63922f,   0.63529f },
  {   0.75294f,   0.74902f,   0.74510f },
  {   0.87059f,   0.87059f,   0.86667f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
