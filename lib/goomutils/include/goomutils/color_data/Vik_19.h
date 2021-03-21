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
static const std::vector<vivid::srgb_t> Vik_19
{
  {   0.00000f,   0.07059f,   0.38039f },
  {   0.00784f,   0.15686f,   0.43529f },
  {   0.01176f,   0.24314f,   0.49020f },
  {   0.02353f,   0.32941f,   0.54510f },
  {   0.11765f,   0.43529f,   0.61569f },
  {   0.27059f,   0.54510f,   0.69020f },
  {   0.44314f,   0.65882f,   0.76863f },
  {   0.61569f,   0.76863f,   0.83922f },
  {   0.78824f,   0.86667f,   0.90588f },
  {   0.92549f,   0.89804f,   0.87843f },
  {   0.91765f,   0.80784f,   0.74118f },
  {   0.87451f,   0.69804f,   0.59608f },
  {   0.82745f,   0.59216f,   0.45490f },
  {   0.78824f,   0.49412f,   0.32549f },
  {   0.74510f,   0.39608f,   0.20000f },
  {   0.67059f,   0.28235f,   0.07843f },
  {   0.54510f,   0.15294f,   0.02353f },
  {   0.44314f,   0.07451f,   0.02745f },
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
