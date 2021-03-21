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
static const std::vector<vivid::srgb_t> LaPaz_16
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.12549f,   0.12941f,   0.44706f },
  {   0.14118f,   0.20392f,   0.49804f },
  {   0.15686f,   0.27451f,   0.54510f },
  {   0.18039f,   0.34118f,   0.58431f },
  {   0.21176f,   0.40392f,   0.61569f },
  {   0.25882f,   0.46667f,   0.63529f },
  {   0.32157f,   0.52157f,   0.64314f },
  {   0.40000f,   0.57255f,   0.63529f },
  {   0.48627f,   0.60784f,   0.61961f },
  {   0.58039f,   0.63529f,   0.59608f },
  {   0.67843f,   0.66667f,   0.58431f },
  {   0.79216f,   0.71765f,   0.61569f },
  {   0.90588f,   0.79608f,   0.70980f },
  {   0.97255f,   0.87843f,   0.83137f },
  {   0.99608f,   0.94902f,   0.95294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
