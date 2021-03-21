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
static const std::vector<vivid::srgb_t> Solar_17
{
  {   0.20000f,   0.07843f,   0.09412f },
  {   0.27843f,   0.10196f,   0.12157f },
  {   0.35686f,   0.12549f,   0.13725f },
  {   0.43529f,   0.14510f,   0.14510f },
  {   0.50980f,   0.17647f,   0.13333f },
  {   0.57647f,   0.21569f,   0.11373f },
  {   0.62745f,   0.27059f,   0.09804f },
  {   0.67451f,   0.32941f,   0.08235f },
  {   0.71373f,   0.39216f,   0.07451f },
  {   0.74902f,   0.45490f,   0.07451f },
  {   0.78039f,   0.52549f,   0.08627f },
  {   0.80784f,   0.59608f,   0.10980f },
  {   0.83137f,   0.67059f,   0.13725f },
  {   0.85098f,   0.74510f,   0.17255f },
  {   0.86667f,   0.82353f,   0.21176f },
  {   0.87451f,   0.90588f,   0.25098f },
  {   0.88235f,   0.99216f,   0.29412f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
