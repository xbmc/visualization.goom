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
static const std::vector<vivid::srgb_t> Tokyo_14
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.22353f,   0.10196f,   0.27059f },
  {   0.33725f,   0.16471f,   0.34118f },
  {   0.44314f,   0.25098f,   0.40784f },
  {   0.50588f,   0.34118f,   0.45882f },
  {   0.53725f,   0.41961f,   0.49020f },
  {   0.55686f,   0.49412f,   0.51373f },
  {   0.56863f,   0.56078f,   0.53333f },
  {   0.58039f,   0.63529f,   0.55294f },
  {   0.60000f,   0.70980f,   0.57647f },
  {   0.64706f,   0.79608f,   0.61176f },
  {   0.75686f,   0.90196f,   0.68627f },
  {   0.89020f,   0.97255f,   0.77255f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
