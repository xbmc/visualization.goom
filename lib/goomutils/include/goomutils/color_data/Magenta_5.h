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
static const std::vector<vivid::srgb_t> Magenta_5
{
  {   0.95294f,   0.79608f,   0.82745f },
  {   0.86667f,   0.53333f,   0.67451f },
  {   0.79216f,   0.41176f,   0.61569f },
  {   0.69412f,   0.30196f,   0.55686f },
  {   0.42353f,   0.12941f,   0.40392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
