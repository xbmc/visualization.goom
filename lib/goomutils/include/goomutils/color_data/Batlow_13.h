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
static const std::vector<vivid::srgb_t> Batlow_13
{
  {   0.00392f,   0.09804f,   0.34902f },
  {   0.04314f,   0.18431f,   0.36471f },
  {   0.07451f,   0.27059f,   0.37647f },
  {   0.13725f,   0.36078f,   0.37647f },
  {   0.24314f,   0.42353f,   0.33333f },
  {   0.36471f,   0.47059f,   0.26667f },
  {   0.50588f,   0.50980f,   0.20000f },
  {   0.66667f,   0.54902f,   0.18431f },
  {   0.83529f,   0.58039f,   0.28235f },
  {   0.95686f,   0.61961f,   0.44314f },
  {   0.99216f,   0.67451f,   0.61961f },
  {   0.99216f,   0.73725f,   0.80000f },
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
