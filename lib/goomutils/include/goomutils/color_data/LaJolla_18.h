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
static const std::vector<vivid::srgb_t> LaJolla_18
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.99216f,   0.96078f,   0.69412f },
  {   0.98431f,   0.91765f,   0.58824f },
  {   0.97255f,   0.86275f,   0.48235f },
  {   0.95294f,   0.78431f,   0.39216f },
  {   0.93333f,   0.70588f,   0.34510f },
  {   0.92157f,   0.63529f,   0.32941f },
  {   0.90588f,   0.56471f,   0.32157f },
  {   0.88627f,   0.49412f,   0.31373f },
  {   0.85098f,   0.41961f,   0.30588f },
  {   0.78039f,   0.34510f,   0.29412f },
  {   0.68235f,   0.29020f,   0.27059f },
  {   0.57647f,   0.25490f,   0.23529f },
  {   0.47059f,   0.22353f,   0.19216f },
  {   0.36863f,   0.19216f,   0.14510f },
  {   0.27059f,   0.16078f,   0.10196f },
  {   0.18039f,   0.13333f,   0.05882f },
  {   0.10196f,   0.10196f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
