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
static const std::vector<vivid::srgb_t> Vik_9
{
  {   0.00000f,   0.07059f,   0.38039f },
  {   0.01176f,   0.26667f,   0.50588f },
  {   0.18824f,   0.49020f,   0.65098f },
  {   0.58039f,   0.74510f,   0.82353f },
  {   0.92549f,   0.89804f,   0.87843f },
  {   0.86275f,   0.67451f,   0.56471f },
  {   0.76471f,   0.44706f,   0.26275f },
  {   0.58039f,   0.18431f,   0.02353f },
  {   0.34902f,   0.00000f,   0.03137f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
