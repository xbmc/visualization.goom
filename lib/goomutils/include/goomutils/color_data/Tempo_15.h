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
static const std::vector<vivid::srgb_t> Tempo_15
{
  {   1.00000f,   0.96471f,   0.95686f },
  {   0.90196f,   0.89804f,   0.85490f },
  {   0.80000f,   0.83922f,   0.75686f },
  {   0.69020f,   0.78431f,   0.67059f },
  {   0.57255f,   0.73333f,   0.60000f },
  {   0.44706f,   0.68627f,   0.54902f },
  {   0.31373f,   0.63529f,   0.51765f },
  {   0.16471f,   0.57647f,   0.49804f },
  {   0.07451f,   0.51765f,   0.48235f },
  {   0.07451f,   0.45098f,   0.45882f },
  {   0.09804f,   0.38431f,   0.42745f },
  {   0.10980f,   0.31765f,   0.38824f },
  {   0.10980f,   0.25098f,   0.34510f },
  {   0.09804f,   0.18431f,   0.30196f },
  {   0.08235f,   0.11373f,   0.26667f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
