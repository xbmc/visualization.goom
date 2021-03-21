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
static const std::vector<vivid::srgb_t> Blues_9
{
  {   0.96863f,   0.98431f,   1.00000f },
  {   0.87059f,   0.92157f,   0.96863f },
  {   0.77647f,   0.85882f,   0.93725f },
  {   0.61961f,   0.79216f,   0.88235f },
  {   0.41961f,   0.68235f,   0.83922f },
  {   0.25882f,   0.57255f,   0.77647f },
  {   0.12941f,   0.44314f,   0.70980f },
  {   0.03137f,   0.31765f,   0.61176f },
  {   0.03137f,   0.18824f,   0.41961f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
