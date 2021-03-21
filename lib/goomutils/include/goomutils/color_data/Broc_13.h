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
static const std::vector<vivid::srgb_t> Broc_13
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16078f,   0.22353f,   0.42353f },
  {   0.18824f,   0.36078f,   0.54902f },
  {   0.35686f,   0.50980f,   0.66275f },
  {   0.54510f,   0.65490f,   0.76078f },
  {   0.74118f,   0.80392f,   0.86275f },
  {   0.92157f,   0.93333f,   0.92549f },
  {   0.87843f,   0.87843f,   0.75686f },
  {   0.77255f,   0.77255f,   0.56078f },
  {   0.60784f,   0.60784f,   0.38431f },
  {   0.44706f,   0.44706f,   0.24706f },
  {   0.28627f,   0.28627f,   0.11373f },
  {   0.14902f,   0.14902f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
