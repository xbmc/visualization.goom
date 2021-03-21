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
static const std::vector<vivid::srgb_t> Oxy_16
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.36078f,   0.02745f,   0.04706f },
  {   0.47451f,   0.01961f,   0.05882f },
  {   0.31373f,   0.30980f,   0.30980f },
  {   0.37255f,   0.37255f,   0.36863f },
  {   0.43529f,   0.43529f,   0.43137f },
  {   0.50588f,   0.50196f,   0.49804f },
  {   0.57255f,   0.56863f,   0.56471f },
  {   0.63922f,   0.63922f,   0.63529f },
  {   0.71765f,   0.71765f,   0.71373f },
  {   0.79608f,   0.79216f,   0.78824f },
  {   0.87451f,   0.87451f,   0.87059f },
  {   0.97255f,   0.99608f,   0.41176f },
  {   0.91373f,   0.90196f,   0.21569f },
  {   0.89412f,   0.78824f,   0.14510f },
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
