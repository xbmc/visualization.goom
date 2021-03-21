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
static const std::vector<vivid::srgb_t> Imola_13
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.13333f,   0.25882f,   0.67059f },
  {   0.16078f,   0.31373f,   0.64314f },
  {   0.18824f,   0.36863f,   0.61569f },
  {   0.22353f,   0.41961f,   0.58039f },
  {   0.27059f,   0.46667f,   0.53725f },
  {   0.32941f,   0.52549f,   0.49804f },
  {   0.40392f,   0.60000f,   0.47451f },
  {   0.48235f,   0.68235f,   0.45490f },
  {   0.56863f,   0.76471f,   0.43529f },
  {   0.66667f,   0.85490f,   0.41176f },
  {   0.82745f,   0.94118f,   0.40000f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
