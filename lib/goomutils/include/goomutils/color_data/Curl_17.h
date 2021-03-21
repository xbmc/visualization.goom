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
static const std::vector<vivid::srgb_t> Curl_17
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10588f,   0.23529f,   0.33725f },
  {   0.10588f,   0.34902f,   0.40784f },
  {   0.06667f,   0.46667f,   0.46667f },
  {   0.17255f,   0.58039f,   0.49804f },
  {   0.41961f,   0.67451f,   0.54118f },
  {   0.63922f,   0.76078f,   0.63529f },
  {   0.82745f,   0.85490f,   0.78431f },
  {   0.99608f,   0.96471f,   0.96078f },
  {   0.93333f,   0.81569f,   0.75686f },
  {   0.88627f,   0.65882f,   0.56863f },
  {   0.84314f,   0.50196f,   0.43137f },
  {   0.76863f,   0.35294f,   0.38039f },
  {   0.65882f,   0.22745f,   0.37647f },
  {   0.52549f,   0.12549f,   0.37647f },
  {   0.36471f,   0.07843f,   0.32941f },
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
