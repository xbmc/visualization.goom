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
static const std::vector<vivid::srgb_t> Amp_7
{
  {   0.94510f,   0.92941f,   0.92549f },
  {   0.87451f,   0.73725f,   0.69020f },
  {   0.81569f,   0.54510f,   0.45098f },
  {   0.75294f,   0.34510f,   0.23137f },
  {   0.65098f,   0.13333f,   0.14510f },
  {   0.45490f,   0.05490f,   0.15686f },
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
