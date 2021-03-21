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
static const std::vector<vivid::srgb_t> Bilbao_15
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.90980f,   0.90980f,   0.90588f },
  {   0.82745f,   0.82353f,   0.80392f },
  {   0.77647f,   0.76078f,   0.69804f },
  {   0.74510f,   0.71765f,   0.60392f },
  {   0.71765f,   0.66667f,   0.51373f },
  {   0.68627f,   0.59608f,   0.43922f },
  {   0.66667f,   0.52549f,   0.39608f },
  {   0.64706f,   0.46667f,   0.36863f },
  {   0.62745f,   0.40392f,   0.34118f },
  {   0.60000f,   0.33333f,   0.30588f },
  {   0.54510f,   0.25490f,   0.24706f },
  {   0.46667f,   0.16863f,   0.16863f },
  {   0.38431f,   0.09020f,   0.09412f },
  {   0.30196f,   0.00000f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
