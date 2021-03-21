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
static const std::vector<vivid::srgb_t> Acton_20
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.23137f,   0.17647f,   0.34510f },
  {   0.29020f,   0.22745f,   0.39608f },
  {   0.34902f,   0.27451f,   0.44706f },
  {   0.41569f,   0.32157f,   0.49412f },
  {   0.48235f,   0.35686f,   0.53333f },
  {   0.55294f,   0.38431f,   0.56078f },
  {   0.61569f,   0.39608f,   0.57255f },
  {   0.67059f,   0.40000f,   0.58039f },
  {   0.73333f,   0.41569f,   0.59608f },
  {   0.79216f,   0.45098f,   0.62353f },
  {   0.82745f,   0.50588f,   0.66667f },
  {   0.83529f,   0.55294f,   0.69804f },
  {   0.83137f,   0.59608f,   0.72941f },
  {   0.82745f,   0.64314f,   0.76078f },
  {   0.83529f,   0.68627f,   0.79608f },
  {   0.84314f,   0.74118f,   0.83137f },
  {   0.85882f,   0.79216f,   0.86667f },
  {   0.88235f,   0.84706f,   0.90588f },
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
