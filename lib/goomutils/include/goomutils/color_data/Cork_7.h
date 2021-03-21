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
static const std::vector<vivid::srgb_t> Cork_7
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.19216f,   0.34902f,   0.54118f },
  {   0.51765f,   0.63137f,   0.74510f },
  {   0.85882f,   0.90196f,   0.89804f },
  {   0.58431f,   0.75686f,   0.60000f },
  {   0.28235f,   0.53725f,   0.26275f },
  {   0.25882f,   0.30196f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
