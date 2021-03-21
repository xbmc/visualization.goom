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
static const std::vector<vivid::srgb_t> Phase_12
{
  {   0.65882f,   0.47059f,   0.05098f },
  {   0.77647f,   0.37647f,   0.20000f },
  {   0.85098f,   0.26275f,   0.38039f },
  {   0.86667f,   0.14902f,   0.65098f },
  {   0.77255f,   0.23529f,   0.88235f },
  {   0.60392f,   0.38431f,   0.95686f },
  {   0.37647f,   0.50196f,   0.89412f },
  {   0.15686f,   0.56863f,   0.72157f },
  {   0.06667f,   0.59216f,   0.54118f },
  {   0.15294f,   0.60392f,   0.30980f },
  {   0.46667f,   0.55294f,   0.07059f },
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
