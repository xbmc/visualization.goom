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
static const std::vector<vivid::srgb_t> Devon_9
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16078f,   0.21961f,   0.41569f },
  {   0.16078f,   0.34510f,   0.56078f },
  {   0.25882f,   0.44706f,   0.73725f },
  {   0.49412f,   0.56078f,   0.86667f },
  {   0.68627f,   0.66667f,   0.93333f },
  {   0.79216f,   0.77647f,   0.95686f },
  {   0.89412f,   0.88627f,   0.98039f },
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
