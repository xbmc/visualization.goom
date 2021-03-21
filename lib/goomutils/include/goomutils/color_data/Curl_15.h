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
static const std::vector<vivid::srgb_t> Curl_15
{
  {   0.08235f,   0.11373f,   0.26667f },
  {   0.10980f,   0.25098f,   0.34510f },
  {   0.09804f,   0.38431f,   0.42745f },
  {   0.07843f,   0.51765f,   0.48627f },
  {   0.31373f,   0.63529f,   0.51765f },
  {   0.57255f,   0.73333f,   0.60000f },
  {   0.80000f,   0.83922f,   0.75686f },
  {   0.99608f,   0.96471f,   0.96078f },
  {   0.92549f,   0.79216f,   0.72549f },
  {   0.87843f,   0.61569f,   0.52157f },
  {   0.81569f,   0.43529f,   0.40000f },
  {   0.70588f,   0.27451f,   0.37647f },
  {   0.56471f,   0.15294f,   0.37647f },
  {   0.39216f,   0.08235f,   0.34118f },
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
