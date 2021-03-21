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
static const std::vector<vivid::srgb_t> LaJolla_19
{
  {   1.00000f,   1.00000f,   0.80000f },
  {   0.99608f,   0.96471f,   0.70196f },
  {   0.98431f,   0.92549f,   0.60392f },
  {   0.97255f,   0.87451f,   0.50196f },
  {   0.95686f,   0.80000f,   0.40784f },
  {   0.94118f,   0.72549f,   0.35294f },
  {   0.92549f,   0.65882f,   0.33333f },
  {   0.90980f,   0.59216f,   0.32157f },
  {   0.89412f,   0.52941f,   0.31765f },
  {   0.87059f,   0.45490f,   0.30980f },
  {   0.82353f,   0.38431f,   0.30196f },
  {   0.74118f,   0.32157f,   0.28235f },
  {   0.64706f,   0.27843f,   0.25882f },
  {   0.54510f,   0.24706f,   0.22745f },
  {   0.45098f,   0.21961f,   0.18431f },
  {   0.35686f,   0.18824f,   0.14118f },
  {   0.25882f,   0.15686f,   0.09412f },
  {   0.17647f,   0.12941f,   0.05490f },
  {   0.10196f,   0.10196f,   0.00392f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
