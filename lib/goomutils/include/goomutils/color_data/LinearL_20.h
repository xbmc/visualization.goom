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
static const std::vector<vivid::srgb_t> LinearL_20
{
  {   0.01569f,   0.01569f,   0.01569f },
  {   0.12549f,   0.04706f,   0.10980f },
  {   0.18039f,   0.08235f,   0.19608f },
  {   0.17647f,   0.10980f,   0.37255f },
  {   0.13333f,   0.17255f,   0.47059f },
  {   0.10588f,   0.23529f,   0.50588f },
  {   0.06275f,   0.30980f,   0.50196f },
  {   0.00392f,   0.38431f,   0.43529f },
  {   0.00000f,   0.45098f,   0.37255f },
  {   0.00000f,   0.52157f,   0.28627f },
  {   0.00000f,   0.58824f,   0.21961f },
  {   0.00000f,   0.65882f,   0.13333f },
  {   0.23137f,   0.70196f,   0.00000f },
  {   0.34118f,   0.75294f,   0.00000f },
  {   0.63137f,   0.77255f,   0.00000f },
  {   0.79608f,   0.79216f,   0.20000f },
  {   0.90588f,   0.81961f,   0.59216f },
  {   0.96863f,   0.86275f,   0.77647f },
  {   0.96863f,   0.93725f,   0.90980f },
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
