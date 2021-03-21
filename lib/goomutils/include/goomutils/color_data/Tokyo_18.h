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
static const std::vector<vivid::srgb_t> Tokyo_18
{
  {   0.10196f,   0.05490f,   0.20392f },
  {   0.19216f,   0.08627f,   0.25098f },
  {   0.28235f,   0.12941f,   0.30588f },
  {   0.37255f,   0.18824f,   0.36078f },
  {   0.44706f,   0.25882f,   0.41176f },
  {   0.49804f,   0.32549f,   0.45098f },
  {   0.52941f,   0.38824f,   0.47843f },
  {   0.54510f,   0.44706f,   0.50196f },
  {   0.55686f,   0.50196f,   0.51765f },
  {   0.56863f,   0.55294f,   0.53333f },
  {   0.57647f,   0.60784f,   0.54510f },
  {   0.58824f,   0.66275f,   0.56078f },
  {   0.60392f,   0.72157f,   0.58039f },
  {   0.64314f,   0.79216f,   0.60784f },
  {   0.71765f,   0.87059f,   0.65882f },
  {   0.82353f,   0.94118f,   0.72941f },
  {   0.91765f,   0.98039f,   0.79216f },
  {   0.99608f,   0.99608f,   0.84706f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
