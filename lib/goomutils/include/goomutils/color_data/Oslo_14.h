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
static const std::vector<vivid::srgb_t> Oslo_14
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.04706f,   0.08235f,   0.12157f },
  {   0.05882f,   0.13725f,   0.21569f },
  {   0.07843f,   0.20392f,   0.32941f },
  {   0.10588f,   0.27451f,   0.43922f },
  {   0.15686f,   0.34902f,   0.56471f },
  {   0.25098f,   0.43137f,   0.68627f },
  {   0.36863f,   0.52157f,   0.76863f },
  {   0.47451f,   0.59216f,   0.79216f },
  {   0.56863f,   0.65098f,   0.78824f },
  {   0.65882f,   0.70588f,   0.79216f },
  {   0.76471f,   0.78431f,   0.81961f },
  {   0.87843f,   0.88235f,   0.89412f },
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
