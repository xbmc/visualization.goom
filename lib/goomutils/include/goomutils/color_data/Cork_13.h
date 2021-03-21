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
static const std::vector<vivid::srgb_t> Cork_13
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.21961f,   0.41961f },
  {   0.19216f,   0.34902f,   0.54118f },
  {   0.34118f,   0.49412f,   0.65098f },
  {   0.51765f,   0.63137f,   0.74510f },
  {   0.70196f,   0.77647f,   0.84314f },
  {   0.85882f,   0.90196f,   0.89804f },
  {   0.74902f,   0.85490f,   0.76078f },
  {   0.58431f,   0.75686f,   0.60000f },
  {   0.41961f,   0.65882f,   0.43922f },
  {   0.28235f,   0.53725f,   0.26275f },
  {   0.25490f,   0.40000f,   0.11373f },
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
