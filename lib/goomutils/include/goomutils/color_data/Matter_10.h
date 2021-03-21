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
static const std::vector<vivid::srgb_t> Matter_10
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98039f,   0.77647f,   0.54902f },
  {   0.95686f,   0.62353f,   0.42745f },
  {   0.92157f,   0.47059f,   0.34510f },
  {   0.85882f,   0.32941f,   0.32549f },
  {   0.75294f,   0.21176f,   0.35686f },
  {   0.62353f,   0.14118f,   0.38431f },
  {   0.47843f,   0.10588f,   0.38431f },
  {   0.32549f,   0.08627f,   0.32941f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
