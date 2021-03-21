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
static const std::vector<vivid::srgb_t> Nuuk_15
{
  {   0.01961f,   0.34902f,   0.54902f },
  {   0.12157f,   0.37255f,   0.52549f },
  {   0.19608f,   0.40000f,   0.50980f },
  {   0.28235f,   0.44314f,   0.51373f },
  {   0.37255f,   0.49020f,   0.53333f },
  {   0.46667f,   0.54510f,   0.56078f },
  {   0.55294f,   0.60000f,   0.58824f },
  {   0.63137f,   0.65098f,   0.59608f },
  {   0.68235f,   0.68627f,   0.58431f },
  {   0.71765f,   0.71765f,   0.56078f },
  {   0.74902f,   0.74510f,   0.53333f },
  {   0.78431f,   0.78039f,   0.51373f },
  {   0.84314f,   0.84314f,   0.52941f },
  {   0.92549f,   0.92157f,   0.60000f },
  {   0.99608f,   0.99608f,   0.69804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
