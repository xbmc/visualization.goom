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
static const std::vector<vivid::srgb_t> ColorBlind_10
{
  {   0.00000f,   0.41961f,   0.64314f },
  {   1.00000f,   0.50196f,   0.05490f },
  {   0.67059f,   0.67059f,   0.67059f },
  {   0.34902f,   0.34902f,   0.34902f },
  {   0.37255f,   0.61961f,   0.81961f },
  {   0.78431f,   0.32157f,   0.00000f },
  {   0.53725f,   0.53725f,   0.53725f },
  {   0.63529f,   0.78431f,   0.92549f },
  {   1.00000f,   0.73725f,   0.47451f },
  {   0.81176f,   0.81176f,   0.81176f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
