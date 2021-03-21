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
static const std::vector<vivid::srgb_t> Devon_16
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.16078f,   0.36078f },
  {   0.15686f,   0.22353f,   0.42353f },
  {   0.15294f,   0.29020f,   0.49412f },
  {   0.16471f,   0.36078f,   0.58431f },
  {   0.21176f,   0.41176f,   0.67843f },
  {   0.29804f,   0.46667f,   0.76863f },
  {   0.42745f,   0.52941f,   0.83922f },
  {   0.55294f,   0.58431f,   0.89020f },
  {   0.65882f,   0.64706f,   0.92549f },
  {   0.72941f,   0.70196f,   0.94510f },
  {   0.78039f,   0.76078f,   0.95686f },
  {   0.83529f,   0.81961f,   0.96471f },
  {   0.89020f,   0.87843f,   0.97647f },
  {   0.94510f,   0.93725f,   0.98824f },
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
