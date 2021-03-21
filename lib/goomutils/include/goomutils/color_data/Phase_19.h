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
static const std::vector<vivid::srgb_t> Phase_19
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.73333f,   0.41569f,   0.14510f },
  {   0.79608f,   0.35294f,   0.23529f },
  {   0.84314f,   0.28627f,   0.34118f },
  {   0.87059f,   0.20000f,   0.49412f },
  {   0.86275f,   0.14510f,   0.66275f },
  {   0.81569f,   0.18431f,   0.81569f },
  {   0.73333f,   0.27451f,   0.91373f },
  {   0.62745f,   0.36471f,   0.95686f },
  {   0.49020f,   0.45098f,   0.94118f },
  {   0.34510f,   0.51373f,   0.87451f },
  {   0.20392f,   0.55686f,   0.76863f },
  {   0.11765f,   0.57647f,   0.65882f },
  {   0.07059f,   0.59216f,   0.54902f },
  {   0.05490f,   0.60000f,   0.43137f },
  {   0.19216f,   0.60000f,   0.27451f },
  {   0.40784f,   0.56863f,   0.09804f },
  {   0.55294f,   0.52157f,   0.05098f },
  {   0.65882f,   0.47059f,   0.05098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
