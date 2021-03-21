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
static const std::vector<vivid::srgb_t> Broc_18
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.18824f,   0.38824f },
  {   0.15686f,   0.27843f,   0.47843f },
  {   0.20392f,   0.38039f,   0.56863f },
  {   0.32157f,   0.48235f,   0.64314f },
  {   0.45490f,   0.58431f,   0.71373f },
  {   0.59216f,   0.69020f,   0.78431f },
  {   0.72941f,   0.79608f,   0.85882f },
  {   0.87059f,   0.89804f,   0.92549f },
  {   0.92941f,   0.93333f,   0.88235f },
  {   0.87451f,   0.87451f,   0.74902f },
  {   0.80000f,   0.80000f,   0.60784f },
  {   0.69804f,   0.69804f,   0.46667f },
  {   0.57647f,   0.57647f,   0.35686f },
  {   0.45882f,   0.45882f,   0.25882f },
  {   0.34902f,   0.34902f,   0.16471f },
  {   0.24314f,   0.24314f,   0.08235f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
