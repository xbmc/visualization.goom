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
static const std::vector<vivid::srgb_t> Batlow_12
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.04706f,   0.19216f,   0.36471f },
  {   0.08235f,   0.29020f,   0.38039f },
  {   0.16471f,   0.38039f,   0.36863f },
  {   0.29020f,   0.44314f,   0.30980f },
  {   0.42745f,   0.48627f,   0.23529f },
  {   0.58431f,   0.52941f,   0.18039f },
  {   0.77255f,   0.56863f,   0.23529f },
  {   0.92941f,   0.60784f,   0.39608f },
  {   0.99216f,   0.66667f,   0.59608f },
  {   0.99216f,   0.73333f,   0.78431f },
  {   0.98039f,   0.80000f,   0.98039f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
