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
static const std::vector<vivid::srgb_t> Oxy_8
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.49020f,   0.01961f,   0.05490f },
  {   0.39216f,   0.38824f,   0.38824f },
  {   0.52941f,   0.52941f,   0.52549f },
  {   0.68627f,   0.68235f,   0.68235f },
  {   0.85098f,   0.85098f,   0.84706f },
  {   0.91765f,   0.91765f,   0.23137f },
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
