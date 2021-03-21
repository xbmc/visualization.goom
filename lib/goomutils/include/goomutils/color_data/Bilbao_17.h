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
static const std::vector<vivid::srgb_t> Bilbao_17
{
  {   1.00000f,   1.00000f,   1.00000f },
  {   0.91765f,   0.91765f,   0.91765f },
  {   0.84314f,   0.84314f,   0.82745f },
  {   0.79216f,   0.78039f,   0.73725f },
  {   0.76078f,   0.73725f,   0.65098f },
  {   0.73333f,   0.69804f,   0.56863f },
  {   0.70980f,   0.64706f,   0.48627f },
  {   0.68235f,   0.58431f,   0.42745f },
  {   0.66667f,   0.52549f,   0.39608f },
  {   0.65098f,   0.47451f,   0.37647f },
  {   0.63529f,   0.41961f,   0.34902f },
  {   0.61569f,   0.36078f,   0.32157f },
  {   0.57647f,   0.29412f,   0.27843f },
  {   0.51765f,   0.22353f,   0.21961f },
  {   0.45098f,   0.15294f,   0.14902f },
  {   0.37647f,   0.08235f,   0.08627f },
  {   0.30196f,   0.00000f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
