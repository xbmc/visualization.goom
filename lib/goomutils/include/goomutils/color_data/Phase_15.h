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
static const std::vector<vivid::srgb_t> Phase_15
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.75294f,   0.40000f,   0.16863f },
  {   0.82353f,   0.31765f,   0.29412f },
  {   0.87059f,   0.21176f,   0.47059f },
  {   0.85882f,   0.14510f,   0.69020f },
  {   0.78431f,   0.22353f,   0.86667f },
  {   0.66275f,   0.34118f,   0.94902f },
  {   0.49020f,   0.45098f,   0.94118f },
  {   0.30196f,   0.52941f,   0.84706f },
  {   0.14510f,   0.56863f,   0.70588f },
  {   0.07843f,   0.58824f,   0.56471f },
  {   0.06667f,   0.60392f,   0.41176f },
  {   0.29412f,   0.59216f,   0.18431f },
  {   0.51765f,   0.53725f,   0.05490f },
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
