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
static const std::vector<vivid::srgb_t> Speed_15
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.95294f,   0.90588f,   0.65490f },
  {   0.90196f,   0.83137f,   0.50196f },
  {   0.83137f,   0.75686f,   0.34118f },
  {   0.74118f,   0.70588f,   0.20392f },
  {   0.62745f,   0.65882f,   0.09412f },
  {   0.50588f,   0.61569f,   0.02353f },
  {   0.37255f,   0.57255f,   0.04706f },
  {   0.24706f,   0.52157f,   0.10196f },
  {   0.12941f,   0.47059f,   0.14510f },
  {   0.05098f,   0.40784f,   0.16863f },
  {   0.05490f,   0.34118f,   0.17647f },
  {   0.08627f,   0.27059f,   0.15686f },
  {   0.09804f,   0.20392f,   0.12157f },
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
