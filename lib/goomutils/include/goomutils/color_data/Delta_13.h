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
static const std::vector<vivid::srgb_t> Delta_13
{
  {   0.06667f,   0.12549f,   0.25098f },
  {   0.15294f,   0.23529f,   0.54510f },
  {   0.10980f,   0.40392f,   0.62745f },
  {   0.20000f,   0.56863f,   0.66275f },
  {   0.42353f,   0.70980f,   0.70196f },
  {   0.73333f,   0.83529f,   0.80000f },
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.88235f,   0.80392f,   0.45098f },
  {   0.66667f,   0.67451f,   0.12549f },
  {   0.38039f,   0.57255f,   0.04314f },
  {   0.09412f,   0.45098f,   0.15686f },
  {   0.07843f,   0.29804f,   0.16471f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
