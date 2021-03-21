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
static const std::vector<vivid::srgb_t> Deep_7
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.64706f,   0.87451f,   0.65490f },
  {   0.36471f,   0.72941f,   0.64314f },
  {   0.28235f,   0.55686f,   0.61961f },
  {   0.24314f,   0.39216f,   0.58431f },
  {   0.25098f,   0.22745f,   0.43137f },
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
