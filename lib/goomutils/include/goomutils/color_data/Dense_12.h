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
static const std::vector<vivid::srgb_t> Dense_12
{
  {   0.90196f,   0.94510f,   0.94510f },
  {   0.74902f,   0.87059f,   0.90196f },
  {   0.61176f,   0.79216f,   0.88627f },
  {   0.50196f,   0.70196f,   0.89020f },
  {   0.45490f,   0.60784f,   0.89412f },
  {   0.45882f,   0.49804f,   0.86667f },
  {   0.47451f,   0.39216f,   0.79608f },
  {   0.47059f,   0.29412f,   0.68627f },
  {   0.44706f,   0.20392f,   0.56078f },
  {   0.39608f,   0.12549f,   0.40784f },
  {   0.31765f,   0.07843f,   0.26275f },
  {   0.21176f,   0.05490f,   0.14118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
