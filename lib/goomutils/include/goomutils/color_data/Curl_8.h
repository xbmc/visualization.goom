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
static const std::vector<vivid::srgb_t> Curl_8
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.09804f,   0.38431f,   0.42745f },
  {   0.31373f,   0.63529f,   0.51765f },
  {   0.80000f,   0.83922f,   0.75686f },
  {   0.92549f,   0.79216f,   0.72549f },
  {   0.81569f,   0.43529f,   0.40000f },
  {   0.56471f,   0.15294f,   0.37647f },
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
