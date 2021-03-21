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
static const std::vector<vivid::srgb_t> Buda_16
{
  {   0.70196f,   0.00392f,   0.70196f },
  {   0.70196f,   0.11765f,   0.64706f },
  {   0.70588f,   0.19216f,   0.60784f },
  {   0.72157f,   0.25882f,   0.58039f },
  {   0.74118f,   0.32157f,   0.56078f },
  {   0.76078f,   0.38039f,   0.54118f },
  {   0.78039f,   0.43529f,   0.52157f },
  {   0.79608f,   0.49412f,   0.50196f },
  {   0.81176f,   0.54902f,   0.48627f },
  {   0.82745f,   0.60784f,   0.47451f },
  {   0.84314f,   0.66667f,   0.45882f },
  {   0.85490f,   0.72549f,   0.44314f },
  {   0.87059f,   0.78824f,   0.42745f },
  {   0.89020f,   0.85098f,   0.41176f },
  {   0.92549f,   0.92157f,   0.40392f },
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
