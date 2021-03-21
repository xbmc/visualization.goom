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
static const std::vector<vivid::srgb_t> Vik_14
{
  {   0.00000f,   0.07059f,   0.38039f },
  {   0.00784f,   0.19216f,   0.45882f },
  {   0.01569f,   0.30980f,   0.53333f },
  {   0.13725f,   0.45098f,   0.62745f },
  {   0.35294f,   0.60392f,   0.72941f },
  {   0.60392f,   0.76078f,   0.83529f },
  {   0.84706f,   0.89412f,   0.91373f },
  {   0.92941f,   0.84314f,   0.79608f },
  {   0.87059f,   0.69020f,   0.58431f },
  {   0.80784f,   0.54510f,   0.39216f },
  {   0.74902f,   0.41176f,   0.21961f },
  {   0.63922f,   0.24314f,   0.05098f },
  {   0.48627f,   0.10588f,   0.02353f },
  {   0.34902f,   0.00000f,   0.03137f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
