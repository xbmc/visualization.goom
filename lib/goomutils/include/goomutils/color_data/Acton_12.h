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
static const std::vector<vivid::srgb_t> Acton_12
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.27451f,   0.21176f,   0.38431f },
  {   0.37647f,   0.29412f,   0.46667f },
  {   0.49804f,   0.36471f,   0.53725f },
  {   0.61176f,   0.39608f,   0.57255f },
  {   0.70980f,   0.40784f,   0.58824f },
  {   0.81176f,   0.47059f,   0.63922f },
  {   0.83529f,   0.55686f,   0.70196f },
  {   0.82745f,   0.63137f,   0.75686f },
  {   0.83922f,   0.71765f,   0.81569f },
  {   0.86667f,   0.80784f,   0.87843f },
  {   0.90196f,   0.90196f,   0.94118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
