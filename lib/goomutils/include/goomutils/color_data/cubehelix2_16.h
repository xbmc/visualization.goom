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
static const std::vector<vivid::srgb_t> cubehelix2_16
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.00000f,   0.10980f,   0.05490f },
  {   0.00000f,   0.20000f,   0.18431f },
  {   0.02745f,   0.25490f,   0.35686f },
  {   0.13725f,   0.27843f,   0.52941f },
  {   0.30588f,   0.28235f,   0.65882f },
  {   0.50588f,   0.28235f,   0.72157f },
  {   0.69412f,   0.30196f,   0.70980f },
  {   0.83922f,   0.35294f,   0.64706f },
  {   0.92157f,   0.44314f,   0.56078f },
  {   0.93333f,   0.55686f,   0.50196f },
  {   0.90196f,   0.68627f,   0.49804f },
  {   0.85882f,   0.80784f,   0.56471f },
  {   0.84706f,   0.90588f,   0.69804f },
  {   0.88627f,   0.96863f,   0.85882f },
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
