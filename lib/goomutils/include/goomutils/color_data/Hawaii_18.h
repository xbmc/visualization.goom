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
static const std::vector<vivid::srgb_t> Hawaii_18
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.56471f,   0.10980f,   0.39216f },
  {   0.57255f,   0.17255f,   0.34118f },
  {   0.58039f,   0.23137f,   0.29412f },
  {   0.58824f,   0.29020f,   0.25098f },
  {   0.59608f,   0.34510f,   0.21176f },
  {   0.60392f,   0.40784f,   0.17255f },
  {   0.61176f,   0.47451f,   0.13725f },
  {   0.61569f,   0.54902f,   0.10980f },
  {   0.60392f,   0.62745f,   0.12941f },
  {   0.56863f,   0.70196f,   0.21569f },
  {   0.51765f,   0.75686f,   0.32941f },
  {   0.46275f,   0.80000f,   0.45490f },
  {   0.40784f,   0.83922f,   0.58431f },
  {   0.37255f,   0.87843f,   0.71765f },
  {   0.40784f,   0.91373f,   0.84314f },
  {   0.54118f,   0.94118f,   0.93725f },
  {   0.70196f,   0.94902f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
