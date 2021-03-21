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
static const std::vector<vivid::srgb_t> Vik_12
{
  {   0.00000f,   0.07059f,   0.38039f },
  {   0.00784f,   0.21176f,   0.47059f },
  {   0.03529f,   0.35686f,   0.56471f },
  {   0.25882f,   0.53725f,   0.68627f },
  {   0.54118f,   0.72157f,   0.80784f },
  {   0.82353f,   0.88235f,   0.91373f },
  {   0.92549f,   0.82745f,   0.77255f },
  {   0.85490f,   0.65098f,   0.53333f },
  {   0.78431f,   0.48627f,   0.31765f },
  {   0.69020f,   0.30980f,   0.10588f },
  {   0.50588f,   0.12157f,   0.02353f },
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
