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
static const std::vector<vivid::srgb_t> Devon_11
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16078f,   0.19608f,   0.39608f },
  {   0.15294f,   0.29020f,   0.49412f },
  {   0.18431f,   0.38431f,   0.62745f },
  {   0.29804f,   0.46667f,   0.76863f },
  {   0.49412f,   0.56078f,   0.86667f },
  {   0.65882f,   0.64706f,   0.92549f },
  {   0.75294f,   0.72941f,   0.94902f },
  {   0.83529f,   0.81961f,   0.96471f },
  {   0.91765f,   0.90980f,   0.98431f },
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
