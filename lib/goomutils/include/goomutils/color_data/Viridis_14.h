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
static const std::vector<vivid::srgb_t> Viridis_14
{
  {   0.26667f,   0.00392f,   0.32941f },
  {   0.28235f,   0.11373f,   0.43529f },
  {   0.27059f,   0.20784f,   0.50588f },
  {   0.23922f,   0.30196f,   0.54118f },
  {   0.20392f,   0.38039f,   0.55294f },
  {   0.16863f,   0.45490f,   0.55686f },
  {   0.14118f,   0.52941f,   0.55686f },
  {   0.12157f,   0.60000f,   0.54118f },
  {   0.14510f,   0.67451f,   0.50980f },
  {   0.25098f,   0.74118f,   0.44706f },
  {   0.40392f,   0.80000f,   0.36078f },
  {   0.59608f,   0.84706f,   0.24314f },
  {   0.79216f,   0.88235f,   0.12157f },
  {   0.99216f,   0.90588f,   0.14510f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
