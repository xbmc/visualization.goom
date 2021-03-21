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
static const std::vector<vivid::srgb_t> Nuuk_18
{
  {   0.01961f,   0.34902f,   0.54902f },
  {   0.10588f,   0.36863f,   0.52941f },
  {   0.16863f,   0.38824f,   0.51373f },
  {   0.23529f,   0.41569f,   0.50980f },
  {   0.30588f,   0.45490f,   0.51765f },
  {   0.38431f,   0.49804f,   0.53725f },
  {   0.46275f,   0.54510f,   0.56078f },
  {   0.53725f,   0.58824f,   0.58039f },
  {   0.60000f,   0.62745f,   0.59216f },
  {   0.65098f,   0.66667f,   0.59216f },
  {   0.69020f,   0.69412f,   0.58039f },
  {   0.71765f,   0.71765f,   0.56078f },
  {   0.74510f,   0.74118f,   0.53725f },
  {   0.77255f,   0.76863f,   0.51765f },
  {   0.81176f,   0.81176f,   0.51765f },
  {   0.87059f,   0.87059f,   0.54902f },
  {   0.93725f,   0.93725f,   0.61569f },
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
