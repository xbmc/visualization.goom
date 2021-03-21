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
static const std::vector<vivid::srgb_t> Magma_20
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.02745f,   0.02353f,   0.10980f },
  {   0.08627f,   0.05882f,   0.23137f },
  {   0.16078f,   0.06667f,   0.35294f },
  {   0.25098f,   0.05882f,   0.45490f },
  {   0.33725f,   0.07843f,   0.49020f },
  {   0.41961f,   0.11373f,   0.50588f },
  {   0.50196f,   0.14510f,   0.50980f },
  {   0.58039f,   0.17255f,   0.50196f },
  {   0.67059f,   0.20000f,   0.48627f },
  {   0.75294f,   0.22745f,   0.46275f },
  {   0.83922f,   0.27059f,   0.42353f },
  {   0.90980f,   0.32549f,   0.38431f },
  {   0.95686f,   0.40392f,   0.36078f },
  {   0.98039f,   0.50588f,   0.37255f },
  {   0.99216f,   0.60392f,   0.41569f },
  {   0.99608f,   0.70588f,   0.48235f },
  {   0.99608f,   0.80000f,   0.56078f },
  {   0.99216f,   0.89804f,   0.65490f },
  {   0.98824f,   0.99216f,   0.74902f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
