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
static const std::vector<vivid::srgb_t> Tofino_12
{
  {   0.87059f,   0.85098f,   1.00000f },
  {   0.62745f,   0.67843f,   0.89412f },
  {   0.39216f,   0.50588f,   0.77255f },
  {   0.21569f,   0.32941f,   0.54510f },
  {   0.12549f,   0.19216f,   0.31765f },
  {   0.06667f,   0.09020f,   0.12941f },
  {   0.06667f,   0.12157f,   0.07059f },
  {   0.11765f,   0.25098f,   0.12941f },
  {   0.19216f,   0.40784f,   0.21176f },
  {   0.33333f,   0.59216f,   0.32549f },
  {   0.59216f,   0.76078f,   0.47059f },
  {   0.85882f,   0.90196f,   0.60784f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
