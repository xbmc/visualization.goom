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
static const std::vector<vivid::srgb_t> LinearL_19
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.12941f,   0.05098f,   0.11373f },
  {   0.17647f,   0.08235f,   0.21569f },
  {   0.17255f,   0.11373f,   0.39216f },
  {   0.12157f,   0.19216f,   0.47451f },
  {   0.10980f,   0.25098f,   0.52549f },
  {   0.03922f,   0.33333f,   0.47843f },
  {   0.00000f,   0.40784f,   0.41569f },
  {   0.00000f,   0.48235f,   0.33725f },
  {   0.00000f,   0.55686f,   0.24706f },
  {   0.00000f,   0.62745f,   0.17647f },
  {   0.15686f,   0.68235f,   0.00000f },
  {   0.30980f,   0.73725f,   0.00000f },
  {   0.56863f,   0.76471f,   0.00000f },
  {   0.77255f,   0.78824f,   0.00000f },
  {   0.88627f,   0.81176f,   0.54118f },
  {   0.96863f,   0.85882f,   0.76471f },
  {   0.96863f,   0.93333f,   0.90588f },
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
