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
static const std::vector<vivid::srgb_t> Acton_9
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.31373f,   0.24314f,   0.41569f },
  {   0.46667f,   0.35294f,   0.52549f },
  {   0.62353f,   0.39608f,   0.57647f },
  {   0.76863f,   0.43137f,   0.60784f },
  {   0.83529f,   0.54902f,   0.69412f },
  {   0.83137f,   0.65098f,   0.76863f },
  {   0.85490f,   0.77255f,   0.85098f },
  {   0.90196f,   0.90196f,   0.94118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
