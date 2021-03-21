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
static const std::vector<vivid::srgb_t> Matter_16
{
  {   0.99608f,   0.92941f,   0.69020f },
  {   0.98431f,   0.83529f,   0.60392f },
  {   0.97647f,   0.74510f,   0.52157f },
  {   0.96078f,   0.65490f,   0.45098f },
  {   0.94510f,   0.56078f,   0.38824f },
  {   0.92157f,   0.47059f,   0.34510f },
  {   0.88627f,   0.38431f,   0.32549f },
  {   0.83922f,   0.30196f,   0.32941f },
  {   0.77647f,   0.23529f,   0.34902f },
  {   0.70196f,   0.18039f,   0.37255f },
  {   0.62353f,   0.14118f,   0.38431f },
  {   0.53725f,   0.11373f,   0.38824f },
  {   0.44706f,   0.10196f,   0.37647f },
  {   0.35686f,   0.09020f,   0.34510f },
  {   0.27059f,   0.07843f,   0.29804f },
  {   0.18431f,   0.05882f,   0.24314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
