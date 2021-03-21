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
static const std::vector<vivid::srgb_t> Curl_12
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10980f,   0.28627f,   0.36863f },
  {   0.07059f,   0.45882f,   0.46275f },
  {   0.25490f,   0.61569f,   0.50980f },
  {   0.60000f,   0.74510f,   0.61569f },
  {   0.87451f,   0.88235f,   0.82745f },
  {   0.94510f,   0.85490f,   0.80784f },
  {   0.87843f,   0.63137f,   0.53725f },
  {   0.80000f,   0.40392f,   0.39216f },
  {   0.64706f,   0.21569f,   0.37647f },
  {   0.43922f,   0.09412f,   0.36078f },
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
