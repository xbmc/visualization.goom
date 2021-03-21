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
static const std::vector<vivid::srgb_t> Balance_16
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.15294f,   0.20000f,   0.47843f },
  {   0.12941f,   0.29804f,   0.71373f },
  {   0.08627f,   0.43922f,   0.73725f },
  {   0.26275f,   0.56078f,   0.72941f },
  {   0.45882f,   0.66667f,   0.74510f },
  {   0.66667f,   0.76078f,   0.79608f },
  {   0.85882f,   0.87059f,   0.87843f },
  {   0.91373f,   0.85098f,   0.83529f },
  {   0.86275f,   0.69804f,   0.64314f },
  {   0.81569f,   0.54510f,   0.45098f },
  {   0.76471f,   0.38824f,   0.27451f },
  {   0.70196f,   0.21961f,   0.14902f },
  {   0.58039f,   0.07451f,   0.15686f },
  {   0.40784f,   0.05882f,   0.14510f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
