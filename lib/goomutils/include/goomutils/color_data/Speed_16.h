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
static const std::vector<vivid::srgb_t> Speed_16
{
  {   1.00000f,   0.99216f,   0.80392f },
  {   0.95294f,   0.91373f,   0.66275f },
  {   0.90588f,   0.83922f,   0.51765f },
  {   0.84706f,   0.77255f,   0.37255f },
  {   0.76863f,   0.71765f,   0.23922f },
  {   0.66667f,   0.67451f,   0.12549f },
  {   0.55686f,   0.63529f,   0.04314f },
  {   0.43922f,   0.59216f,   0.02745f },
  {   0.31765f,   0.54902f,   0.07059f },
  {   0.19608f,   0.50196f,   0.12157f },
  {   0.09412f,   0.45098f,   0.15686f },
  {   0.04314f,   0.38824f,   0.17255f },
  {   0.06275f,   0.32941f,   0.17255f },
  {   0.09020f,   0.26275f,   0.15294f },
  {   0.09804f,   0.20000f,   0.12157f },
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
