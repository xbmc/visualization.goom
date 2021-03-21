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
static const std::vector<vivid::srgb_t> Ice_7
{
  {   0.01569f,   0.02353f,   0.07451f },
  {   0.16078f,   0.15686f,   0.31765f },
  {   0.24706f,   0.29412f,   0.58824f },
  {   0.25882f,   0.48235f,   0.71765f },
  {   0.38039f,   0.65882f,   0.78039f },
  {   0.60392f,   0.82745f,   0.85490f },
  {   0.91765f,   0.99216f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
