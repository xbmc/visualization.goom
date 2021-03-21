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
static const std::vector<vivid::srgb_t> Balance_15
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.15294f,   0.20392f,   0.49020f },
  {   0.10980f,   0.31373f,   0.72941f },
  {   0.12941f,   0.47059f,   0.73333f },
  {   0.31765f,   0.59216f,   0.72941f },
  {   0.53333f,   0.69804f,   0.75686f },
  {   0.74902f,   0.80392f,   0.82745f },
  {   0.94510f,   0.92549f,   0.92157f },
  {   0.88235f,   0.76078f,   0.72157f },
  {   0.83137f,   0.60000f,   0.51765f },
  {   0.78039f,   0.43529f,   0.32549f },
  {   0.72157f,   0.26275f,   0.16863f },
  {   0.60000f,   0.08627f,   0.15294f },
  {   0.41961f,   0.05882f,   0.14510f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
