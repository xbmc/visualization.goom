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
static const std::vector<vivid::srgb_t> Roma_15
{
  {   0.49804f,   0.09804f,   0.00000f },
  {   0.57647f,   0.26667f,   0.06275f },
  {   0.64706f,   0.41176f,   0.12157f },
  {   0.71765f,   0.56078f,   0.18824f },
  {   0.79608f,   0.71373f,   0.30196f },
  {   0.87059f,   0.85098f,   0.49412f },
  {   0.88235f,   0.91373f,   0.66667f },
  {   0.79216f,   0.92157f,   0.78824f },
  {   0.61961f,   0.88235f,   0.84314f },
  {   0.43137f,   0.78039f,   0.83529f },
  {   0.31373f,   0.65882f,   0.79608f },
  {   0.25490f,   0.53725f,   0.74510f },
  {   0.20392f,   0.41569f,   0.69412f },
  {   0.16078f,   0.30588f,   0.64706f },
  {   0.10196f,   0.20000f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
