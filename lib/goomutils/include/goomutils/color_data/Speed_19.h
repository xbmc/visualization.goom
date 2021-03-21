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
static const std::vector<vivid::srgb_t> Speed_19
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.96471f,   0.92549f,   0.68627f },
  {   0.92549f,   0.86275f,   0.56863f },
  {   0.88235f,   0.80392f,   0.45098f },
  {   0.82353f,   0.75294f,   0.32549f },
  {   0.75294f,   0.70980f,   0.21569f },
  {   0.66667f,   0.67451f,   0.12549f },
  {   0.57647f,   0.63922f,   0.05490f },
  {   0.47843f,   0.60784f,   0.02353f },
  {   0.37255f,   0.57255f,   0.04706f },
  {   0.27451f,   0.53333f,   0.09020f },
  {   0.17647f,   0.49412f,   0.12941f },
  {   0.09412f,   0.45098f,   0.15686f },
  {   0.04706f,   0.40000f,   0.17255f },
  {   0.05098f,   0.34902f,   0.17647f },
  {   0.07843f,   0.29804f,   0.16471f },
  {   0.09412f,   0.24314f,   0.14510f },
  {   0.09804f,   0.18824f,   0.11373f },
  {   0.09020f,   0.13725f,   0.07451f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
