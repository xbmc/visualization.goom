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
static const std::vector<vivid::srgb_t> Oxy_12
{
  {   0.25098f,   0.01961f,   0.01961f },
  {   0.40000f,   0.02745f,   0.05490f },
  {   0.54118f,   0.06667f,   0.03529f },
  {   0.38039f,   0.37647f,   0.37647f },
  {   0.46667f,   0.46667f,   0.46275f },
  {   0.55686f,   0.55686f,   0.55294f },
  {   0.65490f,   0.65098f,   0.65098f },
  {   0.75686f,   0.75686f,   0.75294f },
  {   0.86667f,   0.86667f,   0.86275f },
  {   0.94118f,   0.97647f,   0.35294f },
  {   0.90196f,   0.82745f,   0.16471f },
  {   0.86667f,   0.68627f,   0.09804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
