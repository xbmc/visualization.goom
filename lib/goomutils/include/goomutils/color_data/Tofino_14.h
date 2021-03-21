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
static const std::vector<vivid::srgb_t> Tofino_14
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.65882f,   0.70196f,   0.90980f },
  {   0.46275f,   0.56078f,   0.81569f },
  {   0.27843f,   0.40392f,   0.65490f },
  {   0.18039f,   0.27843f,   0.46275f },
  {   0.10980f,   0.16471f,   0.27451f },
  {   0.06275f,   0.08627f,   0.11765f },
  {   0.06275f,   0.10980f,   0.07059f },
  {   0.10196f,   0.21961f,   0.11373f },
  {   0.16471f,   0.35294f,   0.18039f },
  {   0.23922f,   0.49020f,   0.25490f },
  {   0.40392f,   0.65098f,   0.36863f },
  {   0.62745f,   0.77647f,   0.48627f },
  {   0.85882f,   0.90196f,   0.60784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
