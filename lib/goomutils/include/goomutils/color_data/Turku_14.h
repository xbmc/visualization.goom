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
static const std::vector<vivid::srgb_t> Turku_14
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.10980f,   0.10980f,   0.09804f },
  {   0.18431f,   0.18431f,   0.16078f },
  {   0.26667f,   0.26667f,   0.21569f },
  {   0.34510f,   0.34510f,   0.25490f },
  {   0.42745f,   0.42353f,   0.29020f },
  {   0.52157f,   0.50588f,   0.32941f },
  {   0.63137f,   0.58039f,   0.38039f },
  {   0.74902f,   0.63529f,   0.44314f },
  {   0.84314f,   0.65490f,   0.50588f },
  {   0.91373f,   0.67451f,   0.58431f },
  {   0.96863f,   0.73725f,   0.70196f },
  {   0.99608f,   0.81569f,   0.80784f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
