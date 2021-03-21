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
static const std::vector<vivid::srgb_t> Turku_17
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.09412f,   0.09412f,   0.08627f },
  {   0.15686f,   0.15686f,   0.13725f },
  {   0.22353f,   0.22353f,   0.18824f },
  {   0.28627f,   0.28627f,   0.22745f },
  {   0.35294f,   0.35294f,   0.25882f },
  {   0.41961f,   0.41569f,   0.28627f },
  {   0.49020f,   0.48235f,   0.31765f },
  {   0.57647f,   0.54902f,   0.35686f },
  {   0.66667f,   0.60392f,   0.40000f },
  {   0.76078f,   0.63922f,   0.45098f },
  {   0.83137f,   0.65490f,   0.50196f },
  {   0.89412f,   0.66667f,   0.56078f },
  {   0.94902f,   0.70196f,   0.64706f },
  {   0.98431f,   0.76471f,   0.74118f },
  {   0.99608f,   0.83137f,   0.82745f },
  {   1.00000f,   0.90196f,   0.90196f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
