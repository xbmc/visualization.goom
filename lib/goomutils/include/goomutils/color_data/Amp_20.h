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
static const std::vector<vivid::srgb_t> Amp_20
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.91765f,   0.86667f,   0.85490f },
  {   0.89412f,   0.80392f,   0.77647f },
  {   0.87451f,   0.74510f,   0.70196f },
  {   0.85882f,   0.68235f,   0.62353f },
  {   0.83922f,   0.62353f,   0.54902f },
  {   0.81961f,   0.56078f,   0.47059f },
  {   0.80392f,   0.50196f,   0.40000f },
  {   0.78431f,   0.44314f,   0.33333f },
  {   0.76471f,   0.38039f,   0.26275f },
  {   0.74118f,   0.31765f,   0.20392f },
  {   0.71373f,   0.24706f,   0.16078f },
  {   0.68235f,   0.17647f,   0.14118f },
  {   0.63529f,   0.11765f,   0.14510f },
  {   0.57647f,   0.07059f,   0.15686f },
  {   0.51373f,   0.05490f,   0.16078f },
  {   0.43922f,   0.05490f,   0.15294f },
  {   0.37255f,   0.05490f,   0.12941f },
  {   0.30196f,   0.04706f,   0.10196f },
  {   0.23529f,   0.03529f,   0.07059f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
