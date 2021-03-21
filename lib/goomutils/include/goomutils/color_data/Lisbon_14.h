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
static const std::vector<vivid::srgb_t> Lisbon_14
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.69020f,   0.74510f,   0.87451f },
  {   0.49412f,   0.60392f,   0.75686f },
  {   0.29804f,   0.45098f,   0.62745f },
  {   0.15294f,   0.30980f,   0.47059f },
  {   0.08235f,   0.18824f,   0.29412f },
  {   0.07059f,   0.10196f,   0.14118f },
  {   0.12549f,   0.12157f,   0.09412f },
  {   0.24706f,   0.23529f,   0.14902f },
  {   0.39216f,   0.36863f,   0.23529f },
  {   0.53725f,   0.50588f,   0.32549f },
  {   0.70196f,   0.67059f,   0.46667f },
  {   0.85098f,   0.83137f,   0.64314f },
  {   1.00000f,   1.00000f,   0.85098f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
