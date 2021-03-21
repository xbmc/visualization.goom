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
static const std::vector<vivid::srgb_t> Oxy_14
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.38431f,   0.02745f,   0.05098f },
  {   0.50588f,   0.02353f,   0.05098f },
  {   0.34118f,   0.34118f,   0.33725f },
  {   0.40784f,   0.40784f,   0.40392f },
  {   0.48627f,   0.48235f,   0.48235f },
  {   0.56863f,   0.56471f,   0.56471f },
  {   0.64314f,   0.64314f,   0.63922f },
  {   0.73333f,   0.73333f,   0.72941f },
  {   0.82745f,   0.82745f,   0.82353f },
  {   0.92157f,   0.92157f,   0.91373f },
  {   0.91765f,   0.93333f,   0.25098f },
  {   0.89804f,   0.81176f,   0.15686f },
  {   0.86667f,   0.68627f,   0.09804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
