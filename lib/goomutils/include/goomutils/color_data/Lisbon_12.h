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
static const std::vector<vivid::srgb_t> Lisbon_12
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.65882f,   0.72549f,   0.85490f },
  {   0.42745f,   0.55294f,   0.71373f },
  {   0.20392f,   0.36863f,   0.54118f },
  {   0.09020f,   0.21569f,   0.33725f },
  {   0.06667f,   0.10588f,   0.15294f },
  {   0.13725f,   0.12941f,   0.09412f },
  {   0.28235f,   0.26667f,   0.16863f },
  {   0.45098f,   0.42353f,   0.27059f },
  {   0.64314f,   0.61176f,   0.41176f },
  {   0.82745f,   0.80392f,   0.61569f },
  {   1.00000f,   1.00000f,   0.85098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
