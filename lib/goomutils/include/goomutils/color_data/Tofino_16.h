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
static const std::vector<vivid::srgb_t> Tofino_16
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.69020f,   0.72549f,   0.92157f },
  {   0.51373f,   0.60000f,   0.84314f },
  {   0.34118f,   0.46667f,   0.72941f },
  {   0.22353f,   0.34118f,   0.56471f },
  {   0.15294f,   0.23529f,   0.39608f },
  {   0.09804f,   0.14510f,   0.23922f },
  {   0.05882f,   0.08235f,   0.11373f },
  {   0.05882f,   0.10980f,   0.07059f },
  {   0.09412f,   0.19608f,   0.10196f },
  {   0.14118f,   0.30196f,   0.15686f },
  {   0.20000f,   0.42353f,   0.21961f },
  {   0.29020f,   0.55294f,   0.29412f },
  {   0.46275f,   0.68627f,   0.40000f },
  {   0.66275f,   0.79608f,   0.50588f },
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
