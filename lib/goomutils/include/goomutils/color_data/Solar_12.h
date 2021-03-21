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
static const std::vector<vivid::srgb_t> Solar_12
{
  {   0.20000f,   0.07843f,   0.09412f },
  {   0.31373f,   0.11373f,   0.12941f },
  {   0.42745f,   0.14510f,   0.14510f },
  {   0.53725f,   0.18824f,   0.12941f },
  {   0.61961f,   0.25882f,   0.10196f },
  {   0.68627f,   0.34510f,   0.07843f },
  {   0.73725f,   0.43922f,   0.07451f },
  {   0.78431f,   0.53725f,   0.09020f },
  {   0.81961f,   0.64314f,   0.12549f },
  {   0.85098f,   0.75686f,   0.17647f },
  {   0.87059f,   0.87059f,   0.23137f },
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
