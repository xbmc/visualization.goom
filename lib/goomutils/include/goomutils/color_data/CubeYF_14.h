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
static const std::vector<vivid::srgb_t> CubeYF_14
{
  {   0.48235f,   0.00784f,   0.56471f },
  {   0.52549f,   0.11373f,   0.75294f },
  {   0.49804f,   0.26667f,   0.89412f },
  {   0.43137f,   0.38431f,   0.99216f },
  {   0.38039f,   0.50196f,   0.96078f },
  {   0.30980f,   0.60000f,   0.87059f },
  {   0.23529f,   0.69412f,   0.75686f },
  {   0.24314f,   0.75686f,   0.63922f },
  {   0.28627f,   0.81569f,   0.49412f },
  {   0.34118f,   0.86667f,   0.34510f },
  {   0.40784f,   0.90588f,   0.28627f },
  {   0.57647f,   0.92549f,   0.32549f },
  {   0.70588f,   0.92549f,   0.34118f },
  {   0.81961f,   0.92157f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
