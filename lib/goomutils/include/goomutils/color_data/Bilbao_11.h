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
static const std::vector<vivid::srgb_t> Bilbao_11
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.87059f,   0.87059f,   0.86275f },
  {   0.78431f,   0.76863f,   0.72157f },
  {   0.74118f,   0.70980f,   0.58824f },
  {   0.69804f,   0.62353f,   0.46275f },
  {   0.66667f,   0.52549f,   0.39608f },
  {   0.63922f,   0.43922f,   0.36078f },
  {   0.60784f,   0.34902f,   0.31765f },
  {   0.53333f,   0.23529f,   0.23137f },
  {   0.41961f,   0.12157f,   0.12157f },
  {   0.30196f,   0.00000f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
