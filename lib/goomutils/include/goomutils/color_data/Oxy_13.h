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
static const std::vector<vivid::srgb_t> Oxy_13
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.38824f,   0.02745f,   0.05490f },
  {   0.52157f,   0.03922f,   0.04314f },
  {   0.36078f,   0.35686f,   0.35686f },
  {   0.43529f,   0.43529f,   0.43137f },
  {   0.52157f,   0.51765f,   0.51373f },
  {   0.60784f,   0.60392f,   0.60392f },
  {   0.69412f,   0.69412f,   0.69020f },
  {   0.79608f,   0.79216f,   0.78824f },
  {   0.89412f,   0.89412f,   0.89020f },
  {   0.92549f,   0.96078f,   0.30588f },
  {   0.90196f,   0.81569f,   0.15686f },
  {   0.86667f,   0.68627f,   0.09804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
