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
static const std::vector<vivid::srgb_t> Algae_12
{
  {   0.84314f,   0.97647f,   0.81569f },
  {   0.72941f,   0.89412f,   0.68627f },
  {   0.61569f,   0.81961f,   0.56471f },
  {   0.48235f,   0.74902f,   0.45098f },
  {   0.33725f,   0.68627f,   0.36078f },
  {   0.14902f,   0.61961f,   0.31765f },
  {   0.03137f,   0.54118f,   0.30588f },
  {   0.05490f,   0.45882f,   0.28235f },
  {   0.09020f,   0.38039f,   0.24314f },
  {   0.10196f,   0.29804f,   0.19608f },
  {   0.09412f,   0.21961f,   0.14118f },
  {   0.07059f,   0.14118f,   0.07843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
