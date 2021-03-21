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
static const std::vector<vivid::srgb_t> RdYlBu_10
{
  {   0.64706f,   0.00000f,   0.14902f },
  {   0.84314f,   0.18824f,   0.15294f },
  {   0.95686f,   0.42745f,   0.26275f },
  {   0.99216f,   0.68235f,   0.38039f },
  {   0.99608f,   0.87843f,   0.56471f },
  {   0.87843f,   0.95294f,   0.97255f },
  {   0.67059f,   0.85098f,   0.91373f },
  {   0.45490f,   0.67843f,   0.81961f },
  {   0.27059f,   0.45882f,   0.70588f },
  {   0.19216f,   0.21176f,   0.58431f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
