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
static const std::vector<vivid::srgb_t> Berlin_20
{
  {   0.61961f,   0.69020f,   1.00000f },
  {   0.50196f,   0.67451f,   0.94510f },
  {   0.36471f,   0.64706f,   0.86667f },
  {   0.25490f,   0.58039f,   0.75686f },
  {   0.18824f,   0.47843f,   0.61961f },
  {   0.14902f,   0.38431f,   0.49804f },
  {   0.10980f,   0.28627f,   0.37255f },
  {   0.08235f,   0.20000f,   0.25882f },
  {   0.06667f,   0.12549f,   0.15686f },
  {   0.07451f,   0.06667f,   0.07059f },
  {   0.12549f,   0.04314f,   0.01569f },
  {   0.18824f,   0.05882f,   0.00000f },
  {   0.25882f,   0.07451f,   0.00392f },
  {   0.34118f,   0.10588f,   0.02353f },
  {   0.45882f,   0.17647f,   0.09020f },
  {   0.56471f,   0.26667f,   0.18824f },
  {   0.67451f,   0.36863f,   0.30980f },
  {   0.77647f,   0.46667f,   0.42353f },
  {   0.89020f,   0.57647f,   0.55686f },
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
