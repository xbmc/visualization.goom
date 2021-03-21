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
static const std::vector<vivid::srgb_t> Davos_8
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.09020f,   0.21569f,   0.48627f },
  {   0.21961f,   0.39216f,   0.60392f },
  {   0.35294f,   0.50980f,   0.60392f },
  {   0.49020f,   0.60000f,   0.54902f },
  {   0.67059f,   0.73333f,   0.54902f },
  {   0.92157f,   0.92941f,   0.76863f },
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
