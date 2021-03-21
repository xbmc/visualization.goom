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
static const std::vector<vivid::srgb_t> Oslo_19
{
  {   0.00392f,   0.00392f,   0.00392f },
  {   0.03529f,   0.06275f,   0.09412f },
  {   0.05098f,   0.10588f,   0.16078f },
  {   0.06275f,   0.14902f,   0.23529f },
  {   0.07451f,   0.19608f,   0.31765f },
  {   0.09412f,   0.24706f,   0.40000f },
  {   0.12157f,   0.29804f,   0.48235f },
  {   0.16078f,   0.35294f,   0.56863f },
  {   0.21961f,   0.41176f,   0.65882f },
  {   0.31373f,   0.48235f,   0.73725f },
  {   0.39608f,   0.54118f,   0.78039f },
  {   0.47059f,   0.58824f,   0.78824f },
  {   0.53725f,   0.62745f,   0.79216f },
  {   0.60000f,   0.67059f,   0.78824f },
  {   0.66667f,   0.71373f,   0.79216f },
  {   0.74118f,   0.76863f,   0.81176f },
  {   0.83137f,   0.83922f,   0.85882f },
  {   0.91373f,   0.91765f,   0.92157f },
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
