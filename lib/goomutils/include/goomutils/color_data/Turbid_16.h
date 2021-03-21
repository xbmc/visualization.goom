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
static const std::vector<vivid::srgb_t> Turbid_16
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.87451f,   0.88627f,   0.57255f },
  {   0.84314f,   0.81176f,   0.48235f },
  {   0.81176f,   0.73725f,   0.40000f },
  {   0.78431f,   0.66275f,   0.32941f },
  {   0.74902f,   0.59216f,   0.27843f },
  {   0.70980f,   0.52941f,   0.25098f },
  {   0.65882f,   0.46667f,   0.23529f },
  {   0.60392f,   0.41569f,   0.23137f },
  {   0.54118f,   0.36863f,   0.22745f },
  {   0.47451f,   0.32549f,   0.21961f },
  {   0.40392f,   0.28235f,   0.20784f },
  {   0.33725f,   0.24314f,   0.18824f },
  {   0.26667f,   0.20392f,   0.16471f },
  {   0.20000f,   0.16471f,   0.13725f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
