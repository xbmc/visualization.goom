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
static const std::vector<vivid::srgb_t> LaPaz_6
{
  {   0.10196f,   0.04706f,   0.39216f },
  {   0.15686f,   0.27451f,   0.54510f },
  {   0.25882f,   0.46667f,   0.63529f },
  {   0.48627f,   0.60784f,   0.61961f },
  {   0.79216f,   0.71765f,   0.61569f },
  {   0.99608f,   0.94902f,   0.95294f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
