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
static const std::vector<vivid::srgb_t> RdBu_11
{
  {   0.40392f,   0.00000f,   0.12157f },
  {   0.69804f,   0.09412f,   0.16863f },
  {   0.83922f,   0.37647f,   0.30196f },
  {   0.95686f,   0.64706f,   0.50980f },
  {   0.99216f,   0.85882f,   0.78039f },
  {   0.96863f,   0.96863f,   0.96863f },
  {   0.81961f,   0.89804f,   0.94118f },
  {   0.57255f,   0.77255f,   0.87059f },
  {   0.26275f,   0.57647f,   0.76471f },
  {   0.12941f,   0.40000f,   0.67451f },
  {   0.01961f,   0.18824f,   0.38039f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
