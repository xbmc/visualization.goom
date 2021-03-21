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
static const std::vector<vivid::srgb_t> Imola_17
{
  {   0.10196f,   0.20000f,   0.70196f },
  {   0.12549f,   0.24314f,   0.67843f },
  {   0.14510f,   0.28627f,   0.65882f },
  {   0.16863f,   0.32549f,   0.63529f },
  {   0.18824f,   0.36863f,   0.61569f },
  {   0.21569f,   0.40784f,   0.58824f },
  {   0.24706f,   0.44314f,   0.55686f },
  {   0.28235f,   0.48235f,   0.52549f },
  {   0.32941f,   0.52549f,   0.49804f },
  {   0.38039f,   0.57647f,   0.48235f },
  {   0.43922f,   0.63922f,   0.46667f },
  {   0.50196f,   0.70196f,   0.45098f },
  {   0.56863f,   0.76471f,   0.43529f },
  {   0.63922f,   0.83529f,   0.41961f },
  {   0.74118f,   0.90196f,   0.40392f },
  {   0.86667f,   0.95686f,   0.40000f },
  {   1.00000f,   1.00000f,   0.40000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
