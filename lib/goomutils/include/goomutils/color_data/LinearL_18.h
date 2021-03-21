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
static const std::vector<vivid::srgb_t> LinearL_18
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.13725f,   0.05490f,   0.12157f },
  {   0.17647f,   0.08627f,   0.25098f },
  {   0.17255f,   0.12157f,   0.42745f },
  {   0.11373f,   0.20392f,   0.48235f },
  {   0.10588f,   0.27059f,   0.54118f },
  {   0.01569f,   0.36078f,   0.45098f },
  {   0.00000f,   0.43922f,   0.38431f },
  {   0.00000f,   0.51765f,   0.29412f },
  {   0.00000f,   0.59216f,   0.21569f },
  {   0.00000f,   0.66667f,   0.09020f },
  {   0.26667f,   0.71765f,   0.00000f },
  {   0.49020f,   0.76078f,   0.00000f },
  {   0.72941f,   0.78431f,   0.00000f },
  {   0.86667f,   0.81176f,   0.49804f },
  {   0.97255f,   0.84706f,   0.74118f },
  {   0.96863f,   0.92549f,   0.89804f },
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
