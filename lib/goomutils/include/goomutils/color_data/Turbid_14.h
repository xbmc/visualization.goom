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
static const std::vector<vivid::srgb_t> Turbid_14
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.87059f,   0.87451f,   0.55686f },
  {   0.83529f,   0.78824f,   0.45490f },
  {   0.80000f,   0.70196f,   0.36471f },
  {   0.76471f,   0.62353f,   0.29804f },
  {   0.71765f,   0.54118f,   0.25490f },
  {   0.66275f,   0.47059f,   0.23529f },
  {   0.60000f,   0.41176f,   0.23137f },
  {   0.52549f,   0.35686f,   0.22353f },
  {   0.44706f,   0.30588f,   0.21569f },
  {   0.36863f,   0.26275f,   0.20000f },
  {   0.28627f,   0.21569f,   0.17255f },
  {   0.21176f,   0.16863f,   0.14118f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
