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
static const std::vector<vivid::srgb_t> Phase_14
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.76078f,   0.39216f,   0.18039f },
  {   0.83529f,   0.30196f,   0.31765f },
  {   0.87451f,   0.19216f,   0.51765f },
  {   0.84314f,   0.15294f,   0.74510f },
  {   0.74118f,   0.27059f,   0.90980f },
  {   0.58431f,   0.39608f,   0.95686f },
  {   0.40000f,   0.49412f,   0.90588f },
  {   0.19608f,   0.55686f,   0.76078f },
  {   0.09412f,   0.58431f,   0.60392f },
  {   0.04706f,   0.60000f,   0.45098f },
  {   0.25098f,   0.59608f,   0.22353f },
  {   0.49804f,   0.54510f,   0.05882f },
  {   0.65882f,   0.47059f,   0.05098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
