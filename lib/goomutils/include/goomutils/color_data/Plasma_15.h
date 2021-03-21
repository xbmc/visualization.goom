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
static const std::vector<vivid::srgb_t> Plasma_15
{
  {   0.05098f,   0.03137f,   0.52941f },
  {   0.20784f,   0.01569f,   0.59608f },
  {   0.32549f,   0.00784f,   0.63922f },
  {   0.44314f,   0.00000f,   0.65882f },
  {   0.54510f,   0.03922f,   0.64706f },
  {   0.63922f,   0.11765f,   0.60392f },
  {   0.72157f,   0.19608f,   0.53725f },
  {   0.80000f,   0.27843f,   0.47059f },
  {   0.85882f,   0.36078f,   0.40784f },
  {   0.91373f,   0.44314f,   0.34510f },
  {   0.95686f,   0.53333f,   0.28627f },
  {   0.98431f,   0.63137f,   0.22353f },
  {   0.99608f,   0.74118f,   0.16471f },
  {   0.98039f,   0.85490f,   0.14118f },
  {   0.94118f,   0.97647f,   0.12941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
