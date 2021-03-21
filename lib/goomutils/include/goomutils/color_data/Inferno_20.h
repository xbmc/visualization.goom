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
static const std::vector<vivid::srgb_t> Inferno_20
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.03137f,   0.01961f,   0.11373f },
  {   0.09804f,   0.04706f,   0.24314f },
  {   0.18431f,   0.03922f,   0.35686f },
  {   0.27843f,   0.04314f,   0.41569f },
  {   0.36078f,   0.07059f,   0.43137f },
  {   0.44706f,   0.10196f,   0.43137f },
  {   0.52941f,   0.12941f,   0.41961f },
  {   0.60784f,   0.16078f,   0.39216f },
  {   0.69412f,   0.19608f,   0.35294f },
  {   0.76863f,   0.23529f,   0.30588f },
  {   0.84314f,   0.29412f,   0.24706f },
  {   0.89804f,   0.36078f,   0.18824f },
  {   0.94118f,   0.43529f,   0.12549f },
  {   0.97255f,   0.52941f,   0.05490f },
  {   0.98824f,   0.62353f,   0.02745f },
  {   0.98431f,   0.72941f,   0.12157f },
  {   0.96863f,   0.82745f,   0.25098f },
  {   0.94510f,   0.92941f,   0.44314f },
  {   0.98824f,   1.00000f,   0.64314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
