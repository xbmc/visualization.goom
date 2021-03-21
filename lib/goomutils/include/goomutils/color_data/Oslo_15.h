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
static const std::vector<vivid::srgb_t> Oslo_15
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.04314f,   0.07451f,   0.11373f },
  {   0.05882f,   0.12941f,   0.20000f },
  {   0.07451f,   0.19216f,   0.30588f },
  {   0.09804f,   0.25490f,   0.41176f },
  {   0.13725f,   0.32157f,   0.52157f },
  {   0.20000f,   0.39216f,   0.63137f },
  {   0.31373f,   0.48235f,   0.73725f },
  {   0.41961f,   0.55686f,   0.78431f },
  {   0.50588f,   0.61176f,   0.79216f },
  {   0.59216f,   0.66275f,   0.78824f },
  {   0.67843f,   0.72157f,   0.79608f },
  {   0.78039f,   0.80000f,   0.82745f },
  {   0.89020f,   0.89412f,   0.90196f },
  {   1.00000f,   1.00000f,   1.00000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
