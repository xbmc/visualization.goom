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
static const std::vector<vivid::srgb_t> Nuuk_16
{
  {   0.01961f,   0.34902f,   0.54902f },
  {   0.11765f,   0.36863f,   0.52549f },
  {   0.18431f,   0.39608f,   0.51373f },
  {   0.26275f,   0.43137f,   0.50980f },
  {   0.34510f,   0.47843f,   0.52549f },
  {   0.43529f,   0.52941f,   0.55294f },
  {   0.52157f,   0.58039f,   0.57647f },
  {   0.59608f,   0.62745f,   0.59216f },
  {   0.65490f,   0.66667f,   0.59216f },
  {   0.69804f,   0.69804f,   0.57647f },
  {   0.72941f,   0.72549f,   0.55294f },
  {   0.75686f,   0.75686f,   0.52941f },
  {   0.79216f,   0.79216f,   0.51373f },
  {   0.85098f,   0.85098f,   0.53333f },
  {   0.92941f,   0.92941f,   0.60392f },
  {   0.99608f,   0.99608f,   0.69804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
