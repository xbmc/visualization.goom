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
static const std::vector<vivid::srgb_t> Oxy_11
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.41961f,   0.02353f,   0.05882f },
  {   0.31373f,   0.30980f,   0.30980f },
  {   0.40392f,   0.40000f,   0.40000f },
  {   0.50588f,   0.50196f,   0.49804f },
  {   0.60784f,   0.60392f,   0.60392f },
  {   0.71765f,   0.71765f,   0.71373f },
  {   0.83137f,   0.83137f,   0.82745f },
  {   0.97255f,   0.99608f,   0.41176f },
  {   0.90588f,   0.84314f,   0.17255f },
  {   0.86667f,   0.68627f,   0.09804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
