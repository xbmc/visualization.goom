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
static const std::vector<vivid::srgb_t> Gray_15
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.04314f,   0.04314f,   0.04314f },
  {   0.11373f,   0.11373f,   0.11373f },
  {   0.18431f,   0.18431f,   0.18039f },
  {   0.24706f,   0.24706f,   0.24706f },
  {   0.31373f,   0.30980f,   0.30980f },
  {   0.37647f,   0.37255f,   0.37255f },
  {   0.44706f,   0.44314f,   0.44314f },
  {   0.51373f,   0.50980f,   0.50980f },
  {   0.58431f,   0.58039f,   0.58039f },
  {   0.65490f,   0.65490f,   0.65098f },
  {   0.73333f,   0.73333f,   0.72941f },
  {   0.81961f,   0.81961f,   0.81569f },
  {   0.90588f,   0.90588f,   0.90196f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
