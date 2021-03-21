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
static const std::vector<vivid::srgb_t> Balance_20
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.14118f,   0.18039f,   0.42353f },
  {   0.16078f,   0.25098f,   0.61961f },
  {   0.06275f,   0.34902f,   0.74510f },
  {   0.11765f,   0.46275f,   0.73333f },
  {   0.25098f,   0.55294f,   0.72941f },
  {   0.40784f,   0.64314f,   0.73725f },
  {   0.56863f,   0.71765f,   0.76471f },
  {   0.72549f,   0.79216f,   0.81569f },
  {   0.88235f,   0.88235f,   0.89020f },
  {   0.92157f,   0.87059f,   0.85882f },
  {   0.87451f,   0.74118f,   0.69804f },
  {   0.83922f,   0.62353f,   0.55294f },
  {   0.80392f,   0.50980f,   0.40784f },
  {   0.76471f,   0.38039f,   0.26275f },
  {   0.71765f,   0.25098f,   0.16078f },
  {   0.63137f,   0.11373f,   0.14510f },
  {   0.51373f,   0.05490f,   0.16078f },
  {   0.36863f,   0.05490f,   0.12941f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
