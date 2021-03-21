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
static const std::vector<vivid::srgb_t> Devon_20
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16863f,   0.14902f,   0.34510f },
  {   0.16078f,   0.20000f,   0.40000f },
  {   0.15686f,   0.24706f,   0.44706f },
  {   0.15294f,   0.30588f,   0.50980f },
  {   0.16471f,   0.35686f,   0.57647f },
  {   0.19608f,   0.40000f,   0.65490f },
  {   0.24706f,   0.43922f,   0.72549f },
  {   0.33333f,   0.48627f,   0.79216f },
  {   0.44314f,   0.53333f,   0.84706f },
  {   0.54118f,   0.58039f,   0.88235f },
  {   0.63529f,   0.62745f,   0.91765f },
  {   0.69412f,   0.67451f,   0.93725f },
  {   0.74118f,   0.71765f,   0.94510f },
  {   0.78431f,   0.76471f,   0.95686f },
  {   0.82353f,   0.80784f,   0.96471f },
  {   0.87059f,   0.85882f,   0.97255f },
  {   0.90980f,   0.90196f,   0.98039f },
  {   0.95686f,   0.95294f,   0.99216f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
