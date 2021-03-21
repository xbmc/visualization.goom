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
static const std::vector<vivid::srgb_t> Devon_17
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.16078f,   0.35686f },
  {   0.16078f,   0.21961f,   0.41569f },
  {   0.15294f,   0.27843f,   0.48235f },
  {   0.16078f,   0.34510f,   0.56078f },
  {   0.19608f,   0.39608f,   0.65098f },
  {   0.25882f,   0.44706f,   0.73725f },
  {   0.37255f,   0.50196f,   0.81176f },
  {   0.49412f,   0.56078f,   0.86667f },
  {   0.60392f,   0.60784f,   0.90588f },
  {   0.68627f,   0.66667f,   0.93333f },
  {   0.74510f,   0.72157f,   0.94902f },
  {   0.79216f,   0.77647f,   0.95686f },
  {   0.84314f,   0.83137f,   0.96863f },
  {   0.89412f,   0.88627f,   0.98039f },
  {   0.94902f,   0.94118f,   0.98824f },
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
