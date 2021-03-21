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
static const std::vector<vivid::srgb_t> Davos_15
{
  {   0.00000f,   0.01961f,   0.29020f },
  {   0.03922f,   0.12157f,   0.39216f },
  {   0.09020f,   0.21569f,   0.48627f },
  {   0.15294f,   0.30980f,   0.56471f },
  {   0.21961f,   0.39216f,   0.60392f },
  {   0.28627f,   0.45882f,   0.61569f },
  {   0.35294f,   0.50980f,   0.60392f },
  {   0.42353f,   0.55686f,   0.57647f },
  {   0.49020f,   0.60000f,   0.54902f },
  {   0.56863f,   0.65490f,   0.52941f },
  {   0.67059f,   0.73333f,   0.54902f },
  {   0.80392f,   0.83529f,   0.63137f },
  {   0.92157f,   0.92941f,   0.76863f },
  {   0.97647f,   0.97647f,   0.89020f },
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
