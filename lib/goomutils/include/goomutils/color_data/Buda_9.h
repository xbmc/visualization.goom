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
static const std::vector<vivid::srgb_t> Buda_9
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.70196f,   0.18431f,   0.61176f },
  {   0.73725f,   0.30588f,   0.56471f },
  {   0.77255f,   0.41569f,   0.52941f },
  {   0.80392f,   0.52157f,   0.49412f },
  {   0.83137f,   0.62745f,   0.46667f },
  {   0.85882f,   0.74118f,   0.43922f },
  {   0.89020f,   0.85882f,   0.41176f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
