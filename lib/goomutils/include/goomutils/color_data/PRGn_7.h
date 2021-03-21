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
static const std::vector<vivid::srgb_t> PRGn_7
{
  {   0.46275f,   0.16471f,   0.51373f },
  {   0.68627f,   0.55294f,   0.76471f },
  {   0.90588f,   0.83137f,   0.90980f },
  {   0.96863f,   0.96863f,   0.96863f },
  {   0.85098f,   0.94118f,   0.82745f },
  {   0.49804f,   0.74902f,   0.48235f },
  {   0.10588f,   0.47059f,   0.21569f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
