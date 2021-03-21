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
static const std::vector<vivid::srgb_t> Oleron_18
{
  {   0.10196f,   0.14902f,   0.34902f },
  {   0.19216f,   0.23922f,   0.43922f },
  {   0.28627f,   0.33333f,   0.53333f },
  {   0.38431f,   0.43529f,   0.63529f },
  {   0.48627f,   0.53725f,   0.73725f },
  {   0.59608f,   0.64314f,   0.84314f },
  {   0.69804f,   0.74902f,   0.93333f },
  {   0.78431f,   0.83529f,   0.97255f },
  {   0.86275f,   0.91373f,   0.99216f },
  {   0.17255f,   0.31765f,   0.00000f },
  {   0.30196f,   0.36078f,   0.00392f },
  {   0.43137f,   0.41569f,   0.07843f },
  {   0.56471f,   0.49804f,   0.20784f },
  {   0.69412f,   0.58431f,   0.34118f },
  {   0.82745f,   0.68627f,   0.47843f },
  {   0.93333f,   0.79608f,   0.62353f },
  {   0.97255f,   0.89412f,   0.76471f },
  {   0.99216f,   0.99216f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
