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
static const std::vector<vivid::srgb_t> Hawaii_15
{
  {   0.54902f,   0.00784f,   0.45098f },
  {   0.56471f,   0.12157f,   0.38431f },
  {   0.57647f,   0.19608f,   0.32157f },
  {   0.58431f,   0.27059f,   0.26667f },
  {   0.59608f,   0.33725f,   0.21961f },
  {   0.60392f,   0.41176f,   0.17255f },
  {   0.61176f,   0.49412f,   0.12549f },
  {   0.61176f,   0.58824f,   0.10980f },
  {   0.58039f,   0.68235f,   0.18824f },
  {   0.52157f,   0.75294f,   0.32157f },
  {   0.45490f,   0.80784f,   0.47451f },
  {   0.39216f,   0.85490f,   0.62745f },
  {   0.38039f,   0.90196f,   0.79216f },
  {   0.50980f,   0.93725f,   0.92157f },
  {   0.70196f,   0.94902f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
