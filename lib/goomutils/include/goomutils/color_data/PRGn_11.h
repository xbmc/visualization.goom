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
static const std::vector<vivid::srgb_t> PRGn_11
{
  {   0.25098f,   0.00000f,   0.29412f },
  {   0.46275f,   0.16471f,   0.51373f },
  {   0.60000f,   0.43922f,   0.67059f },
  {   0.76078f,   0.64706f,   0.81176f },
  {   0.90588f,   0.83137f,   0.90980f },
  {   0.96863f,   0.96863f,   0.96863f },
  {   0.85098f,   0.94118f,   0.82745f },
  {   0.65098f,   0.85882f,   0.62745f },
  {   0.35294f,   0.68235f,   0.38039f },
  {   0.10588f,   0.47059f,   0.21569f },
  {   0.00000f,   0.26667f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
