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
static const std::vector<vivid::srgb_t> Cork_14
{
  {   0.17255f,   0.10196f,   0.29804f },
  {   0.16471f,   0.21176f,   0.41176f },
  {   0.18039f,   0.32941f,   0.52157f },
  {   0.29804f,   0.46275f,   0.62745f },
  {   0.45882f,   0.58824f,   0.71373f },
  {   0.63137f,   0.72157f,   0.80784f },
  {   0.80392f,   0.85490f,   0.89412f },
  {   0.83529f,   0.90196f,   0.85098f },
  {   0.68627f,   0.81569f,   0.69804f },
  {   0.52941f,   0.72549f,   0.54510f },
  {   0.38039f,   0.63137f,   0.40000f },
  {   0.26667f,   0.50980f,   0.23137f },
  {   0.25490f,   0.39608f,   0.10980f },
  {   0.25882f,   0.30196f,   0.01176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
