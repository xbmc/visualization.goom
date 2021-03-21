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
static const std::vector<vivid::srgb_t> Davos_11
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.06275f,   0.16471f,   0.43529f },
  {   0.13725f,   0.29020f,   0.54902f },
  {   0.22745f,   0.40392f,   0.60784f },
  {   0.32941f,   0.49020f,   0.61176f },
  {   0.42353f,   0.55686f,   0.57647f },
  {   0.51765f,   0.61961f,   0.53725f },
  {   0.64314f,   0.71373f,   0.54118f },
  {   0.83137f,   0.85882f,   0.65882f },
  {   0.96078f,   0.96078f,   0.84314f },
  {   0.99608f,   0.99608f,   0.99608f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
