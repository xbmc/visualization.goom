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
static const std::vector<vivid::srgb_t> Acton_14
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.26275f,   0.20000f,   0.37255f },
  {   0.34510f,   0.27059f,   0.44314f },
  {   0.44314f,   0.33725f,   0.50980f },
  {   0.54118f,   0.38039f,   0.55686f },
  {   0.63137f,   0.39608f,   0.57647f },
  {   0.72157f,   0.41176f,   0.58824f },
  {   0.80392f,   0.46275f,   0.63137f },
  {   0.83529f,   0.54118f,   0.69020f },
  {   0.83137f,   0.60392f,   0.73725f },
  {   0.83137f,   0.67059f,   0.78039f },
  {   0.84706f,   0.74510f,   0.83529f },
  {   0.87059f,   0.81961f,   0.88627f },
  {   0.90196f,   0.90196f,   0.94118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
