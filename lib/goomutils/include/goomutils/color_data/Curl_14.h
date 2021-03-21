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
static const std::vector<vivid::srgb_t> Curl_14
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10980f,   0.25882f,   0.35294f },
  {   0.09020f,   0.40392f,   0.43922f },
  {   0.10980f,   0.54902f,   0.49412f },
  {   0.39608f,   0.66667f,   0.53333f },
  {   0.67059f,   0.77255f,   0.65882f },
  {   0.89412f,   0.89412f,   0.84706f },
  {   0.95294f,   0.87451f,   0.83529f },
  {   0.89412f,   0.68235f,   0.59608f },
  {   0.83922f,   0.48627f,   0.42353f },
  {   0.73725f,   0.30980f,   0.37647f },
  {   0.59216f,   0.16863f,   0.38039f },
  {   0.40000f,   0.08627f,   0.34510f },
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
