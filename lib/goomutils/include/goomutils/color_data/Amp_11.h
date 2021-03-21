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
static const std::vector<vivid::srgb_t> Amp_11
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.89804f,   0.80784f,   0.78431f },
  {   0.86275f,   0.69412f,   0.63922f },
  {   0.82745f,   0.58431f,   0.49804f },
  {   0.79216f,   0.46667f,   0.35686f },
  {   0.75294f,   0.34510f,   0.23137f },
  {   0.70196f,   0.21961f,   0.14902f },
  {   0.61961f,   0.10196f,   0.14902f },
  {   0.49804f,   0.05490f,   0.16078f },
  {   0.36078f,   0.05490f,   0.12941f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
