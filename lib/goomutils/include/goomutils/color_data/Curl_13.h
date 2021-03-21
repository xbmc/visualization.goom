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
static const std::vector<vivid::srgb_t> Curl_13
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10980f,   0.27451f,   0.36078f },
  {   0.08235f,   0.42745f,   0.45098f },
  {   0.17255f,   0.58039f,   0.49804f },
  {   0.49020f,   0.70196f,   0.56471f },
  {   0.76471f,   0.81961f,   0.72941f },
  {   0.99608f,   0.96471f,   0.96078f },
  {   0.91373f,   0.76078f,   0.68627f },
  {   0.85882f,   0.54902f,   0.46667f },
  {   0.76863f,   0.35294f,   0.38039f },
  {   0.61569f,   0.18824f,   0.37647f },
  {   0.42353f,   0.09020f,   0.35294f },
  {   0.20392f,   0.05098f,   0.20784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
