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
static const std::vector<vivid::srgb_t> Bamako_20
{
  {   0.00000f,   0.25098f,   0.29804f },
  {   0.03529f,   0.27059f,   0.28235f },
  {   0.07059f,   0.29020f,   0.26275f },
  {   0.10196f,   0.31373f,   0.24314f },
  {   0.14118f,   0.33725f,   0.21961f },
  {   0.17647f,   0.36078f,   0.19608f },
  {   0.21569f,   0.38824f,   0.17255f },
  {   0.25490f,   0.41176f,   0.14902f },
  {   0.29804f,   0.44314f,   0.12549f },
  {   0.35294f,   0.47451f,   0.09412f },
  {   0.40784f,   0.50980f,   0.06275f },
  {   0.47451f,   0.54118f,   0.02745f },
  {   0.54118f,   0.56078f,   0.01176f },
  {   0.61176f,   0.58039f,   0.04314f },
  {   0.70588f,   0.63137f,   0.12549f },
  {   0.78824f,   0.69804f,   0.21961f },
  {   0.85882f,   0.75686f,   0.32157f },
  {   0.90588f,   0.80784f,   0.41569f },
  {   0.95686f,   0.85490f,   0.51373f },
  {   1.00000f,   0.89804f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
