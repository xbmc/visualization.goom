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
static const std::vector<vivid::srgb_t> Cork_19
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16863f,   0.18039f,   0.37647f },
  {   0.16471f,   0.26275f,   0.45882f },
  {   0.19216f,   0.34902f,   0.54118f },
  {   0.28235f,   0.44706f,   0.61961f },
  {   0.39608f,   0.54118f,   0.68235f },
  {   0.51765f,   0.63137f,   0.74510f },
  {   0.63922f,   0.72549f,   0.81176f },
  {   0.76471f,   0.82353f,   0.87451f },
  {   0.85882f,   0.90196f,   0.89804f },
  {   0.80392f,   0.88235f,   0.81176f },
  {   0.69412f,   0.81961f,   0.70588f },
  {   0.58431f,   0.75686f,   0.60000f },
  {   0.47451f,   0.69020f,   0.49020f },
  {   0.36863f,   0.62353f,   0.38431f },
  {   0.28235f,   0.53725f,   0.26275f },
  {   0.25098f,   0.43922f,   0.15294f },
  {   0.25490f,   0.36471f,   0.07843f },
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
