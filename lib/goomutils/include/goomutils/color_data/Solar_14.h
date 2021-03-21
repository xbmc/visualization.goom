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
static const std::vector<vivid::srgb_t> Solar_14
{
  {   0.20000f,   0.07843f,   0.09412f },
  {   0.29804f,   0.10980f,   0.12549f },
  {   0.39216f,   0.13333f,   0.14118f },
  {   0.48627f,   0.16471f,   0.13725f },
  {   0.56863f,   0.21176f,   0.11765f },
  {   0.63529f,   0.27843f,   0.09412f },
  {   0.69020f,   0.35294f,   0.07843f },
  {   0.73333f,   0.43137f,   0.07451f },
  {   0.77647f,   0.51765f,   0.08627f },
  {   0.80784f,   0.60392f,   0.10980f },
  {   0.83529f,   0.69412f,   0.14902f },
  {   0.85882f,   0.78824f,   0.19216f },
  {   0.87451f,   0.88627f,   0.23922f },
  {   0.88235f,   0.99216f,   0.29412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
