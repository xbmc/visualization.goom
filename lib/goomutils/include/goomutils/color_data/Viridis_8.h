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
static const std::vector<vivid::srgb_t> Viridis_8
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.27451f,   0.19608f,   0.49412f },
  {   0.21176f,   0.36078f,   0.55294f },
  {   0.15294f,   0.49804f,   0.55686f },
  {   0.12157f,   0.63137f,   0.52941f },
  {   0.29020f,   0.75686f,   0.42745f },
  {   0.62745f,   0.85490f,   0.22353f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
