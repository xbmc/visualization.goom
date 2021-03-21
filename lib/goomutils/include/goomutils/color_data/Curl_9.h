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
static const std::vector<vivid::srgb_t> Curl_9
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10588f,   0.34902f,   0.40784f },
  {   0.17255f,   0.58039f,   0.49804f },
  {   0.63922f,   0.76078f,   0.63529f },
  {   0.99608f,   0.96471f,   0.96078f },
  {   0.88627f,   0.65882f,   0.56863f },
  {   0.76863f,   0.35294f,   0.38039f },
  {   0.52549f,   0.12549f,   0.37647f },
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
