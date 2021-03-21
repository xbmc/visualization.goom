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
static const std::vector<vivid::srgb_t> Cork_12
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.23137f,   0.43137f },
  {   0.21176f,   0.37647f,   0.56078f },
  {   0.38824f,   0.53333f,   0.67843f },
  {   0.58824f,   0.68627f,   0.78431f },
  {   0.78824f,   0.84314f,   0.88627f },
  {   0.82353f,   0.89412f,   0.83529f },
  {   0.64706f,   0.79216f,   0.65882f },
  {   0.46667f,   0.68627f,   0.48627f },
  {   0.29412f,   0.55686f,   0.29020f },
  {   0.25490f,   0.41176f,   0.12549f },
  {   0.25882f,   0.30196f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
