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
static const std::vector<vivid::srgb_t> Curl_10
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10980f,   0.32549f,   0.39216f },
  {   0.09020f,   0.53333f,   0.49020f },
  {   0.49020f,   0.70196f,   0.56471f },
  {   0.84706f,   0.86667f,   0.80000f },
  {   0.93725f,   0.82745f,   0.77647f },
  {   0.85882f,   0.54902f,   0.46667f },
  {   0.72549f,   0.29412f,   0.37647f },
  {   0.49020f,   0.10980f,   0.37255f },
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
