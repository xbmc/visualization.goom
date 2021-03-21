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
static const std::vector<vivid::srgb_t> Deep_6
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.57255f,   0.84706f,   0.64314f },
  {   0.32157f,   0.65882f,   0.63922f },
  {   0.25098f,   0.45882f,   0.59608f },
  {   0.25490f,   0.25098f,   0.48235f },
  {   0.15686f,   0.10196f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
