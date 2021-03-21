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
static const std::vector<vivid::srgb_t> Plasma_20
{
  {   0.05098f,   0.03137f,   0.52941f },
  {   0.17255f,   0.01961f,   0.58039f },
  {   0.26667f,   0.01176f,   0.61961f },
  {   0.34902f,   0.00392f,   0.64706f },
  {   0.43529f,   0.00000f,   0.65882f },
  {   0.51373f,   0.01961f,   0.65490f },
  {   0.58824f,   0.07451f,   0.63137f },
  {   0.65490f,   0.12941f,   0.59216f },
  {   0.71373f,   0.18824f,   0.54510f },
  {   0.77255f,   0.25098f,   0.49412f },
  {   0.81961f,   0.30588f,   0.44706f },
  {   0.86667f,   0.36863f,   0.40000f },
  {   0.90588f,   0.43137f,   0.35686f },
  {   0.93725f,   0.49412f,   0.31373f },
  {   0.96863f,   0.56471f,   0.26667f },
  {   0.98431f,   0.63529f,   0.21961f },
  {   0.99608f,   0.71765f,   0.17647f },
  {   0.99216f,   0.79608f,   0.14902f },
  {   0.96863f,   0.88627f,   0.14510f },
  {   0.94118f,   0.97647f,   0.12941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
