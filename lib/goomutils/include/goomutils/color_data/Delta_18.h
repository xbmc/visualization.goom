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
static const std::vector<vivid::srgb_t> Delta_18
{
  {   0.06667f,   0.12549f,   0.25098f },
  {   0.13725f,   0.20000f,   0.44706f },
  {   0.11765f,   0.30196f,   0.61176f },
  {   0.11765f,   0.42353f,   0.63137f },
  {   0.17647f,   0.53725f,   0.65490f },
  {   0.28627f,   0.64706f,   0.68235f },
  {   0.50196f,   0.74118f,   0.71765f },
  {   0.71373f,   0.82745f,   0.79216f },
  {   0.90196f,   0.92941f,   0.87451f },
  {   0.96078f,   0.92157f,   0.67843f },
  {   0.87059f,   0.79608f,   0.42353f },
  {   0.72941f,   0.69804f,   0.18824f },
  {   0.53333f,   0.62745f,   0.03137f },
  {   0.32157f,   0.55294f,   0.07059f },
  {   0.12157f,   0.46667f,   0.14902f },
  {   0.04706f,   0.36078f,   0.17647f },
  {   0.09412f,   0.24706f,   0.14902f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
