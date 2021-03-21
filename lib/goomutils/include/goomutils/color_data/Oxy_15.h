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
static const std::vector<vivid::srgb_t> Oxy_15
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.36471f,   0.02745f,   0.04706f },
  {   0.49020f,   0.01961f,   0.05490f },
  {   0.32549f,   0.32549f,   0.32549f },
  {   0.39216f,   0.38824f,   0.38824f },
  {   0.46275f,   0.45882f,   0.45490f },
  {   0.52941f,   0.52941f,   0.52549f },
  {   0.60784f,   0.60392f,   0.60392f },
  {   0.68627f,   0.68235f,   0.68235f },
  {   0.76471f,   0.76471f,   0.76078f },
  {   0.85098f,   0.85098f,   0.84706f },
  {   0.94118f,   0.94118f,   0.93725f },
  {   0.91765f,   0.91765f,   0.23137f },
  {   0.89804f,   0.79608f,   0.14902f },
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
