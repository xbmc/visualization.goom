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
static const std::vector<vivid::srgb_t> Deep_18
{
  {   0.99216f,   0.99608f,   0.80000f },
  {   0.87451f,   0.94902f,   0.73333f },
  {   0.74902f,   0.90588f,   0.68235f },
  {   0.62353f,   0.86667f,   0.64706f },
  {   0.49804f,   0.81961f,   0.63922f },
  {   0.40392f,   0.76471f,   0.64314f },
  {   0.34902f,   0.70588f,   0.64314f },
  {   0.31765f,   0.64706f,   0.63529f },
  {   0.29412f,   0.58824f,   0.62745f },
  {   0.27451f,   0.52941f,   0.61176f },
  {   0.25490f,   0.47059f,   0.60000f },
  {   0.24314f,   0.41176f,   0.58824f },
  {   0.24314f,   0.34902f,   0.57255f },
  {   0.25490f,   0.28627f,   0.53333f },
  {   0.25098f,   0.23529f,   0.44314f },
  {   0.22745f,   0.18824f,   0.34510f },
  {   0.19608f,   0.14510f,   0.25490f },
  {   0.15686f,   0.10196f,   0.17255f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
