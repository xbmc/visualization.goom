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
static const std::vector<vivid::srgb_t> Tofino_8
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.49412f,   0.58431f,   0.83137f },
  {   0.20000f,   0.30980f,   0.51373f },
  {   0.07843f,   0.11373f,   0.18039f },
  {   0.07843f,   0.15294f,   0.08627f },
  {   0.18039f,   0.38431f,   0.20000f },
  {   0.43922f,   0.67059f,   0.38824f },
  {   0.85882f,   0.90196f,   0.60784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
