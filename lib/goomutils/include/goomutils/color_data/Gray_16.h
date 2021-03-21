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
static const std::vector<vivid::srgb_t> Gray_16
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.03922f,   0.03922f,   0.03922f },
  {   0.10980f,   0.10588f,   0.10588f },
  {   0.16863f,   0.16863f,   0.16863f },
  {   0.23137f,   0.22745f,   0.22745f },
  {   0.29020f,   0.29020f,   0.28627f },
  {   0.35294f,   0.34902f,   0.34902f },
  {   0.41176f,   0.41176f,   0.40784f },
  {   0.47451f,   0.47451f,   0.47059f },
  {   0.54118f,   0.53725f,   0.53725f },
  {   0.60784f,   0.60392f,   0.60392f },
  {   0.67843f,   0.67451f,   0.67451f },
  {   0.75294f,   0.74902f,   0.74510f },
  {   0.82745f,   0.82745f,   0.82353f },
  {   0.90980f,   0.90980f,   0.90588f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
