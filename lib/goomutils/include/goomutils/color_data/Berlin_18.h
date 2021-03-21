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
static const std::vector<vivid::srgb_t> Berlin_18
{
  {   0.61961f,   0.69020f,   1.00000f },
  {   0.48235f,   0.67451f,   0.93333f },
  {   0.33725f,   0.63529f,   0.84314f },
  {   0.22353f,   0.54510f,   0.70588f },
  {   0.16863f,   0.43529f,   0.56078f },
  {   0.12549f,   0.32941f,   0.42353f },
  {   0.09020f,   0.22745f,   0.29412f },
  {   0.06667f,   0.13725f,   0.17255f },
  {   0.07059f,   0.07059f,   0.07843f },
  {   0.12941f,   0.04314f,   0.01176f },
  {   0.20000f,   0.05882f,   0.00000f },
  {   0.28235f,   0.08235f,   0.00784f },
  {   0.38824f,   0.12941f,   0.04706f },
  {   0.51765f,   0.22353f,   0.14118f },
  {   0.63529f,   0.33333f,   0.26667f },
  {   0.75294f,   0.44314f,   0.39608f },
  {   0.87451f,   0.56078f,   0.53725f },
  {   1.00000f,   0.67843f,   0.67843f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
