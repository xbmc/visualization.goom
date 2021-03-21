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
static const std::vector<vivid::srgb_t> OrRd_9
{
  {   1.00000f,   0.96863f,   0.92549f },
  {   0.99608f,   0.90980f,   0.78431f },
  {   0.99216f,   0.83137f,   0.61961f },
  {   0.99216f,   0.73333f,   0.51765f },
  {   0.98824f,   0.55294f,   0.34902f },
  {   0.93725f,   0.39608f,   0.28235f },
  {   0.84314f,   0.18824f,   0.12157f },
  {   0.70196f,   0.00000f,   0.00000f },
  {   0.49804f,   0.00000f,   0.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
