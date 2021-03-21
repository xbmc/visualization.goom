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
static const std::vector<vivid::srgb_t> Oxy_10
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.43529f,   0.02353f,   0.05882f },
  {   0.33333f,   0.32941f,   0.32941f },
  {   0.43529f,   0.43529f,   0.43137f },
  {   0.54510f,   0.54510f,   0.54118f },
  {   0.66667f,   0.66667f,   0.66275f },
  {   0.79608f,   0.79216f,   0.78824f },
  {   0.93333f,   0.93333f,   0.92549f },
  {   0.90980f,   0.86275f,   0.18824f },
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
