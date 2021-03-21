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
static const std::vector<vivid::srgb_t> Deep_15
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.85098f,   0.94118f,   0.72157f },
  {   0.69804f,   0.89020f,   0.66667f },
  {   0.53725f,   0.83529f,   0.63922f },
  {   0.41569f,   0.77255f,   0.64314f },
  {   0.34510f,   0.70196f,   0.64314f },
  {   0.30980f,   0.63137f,   0.63529f },
  {   0.28235f,   0.55686f,   0.61961f },
  {   0.25882f,   0.48627f,   0.60392f },
  {   0.24314f,   0.41569f,   0.58824f },
  {   0.24314f,   0.34118f,   0.56863f },
  {   0.25490f,   0.26667f,   0.50588f },
  {   0.23922f,   0.20784f,   0.38431f },
  {   0.20392f,   0.15686f,   0.27451f },
  {   0.15686f,   0.10196f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
