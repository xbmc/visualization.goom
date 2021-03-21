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
static const std::vector<vivid::srgb_t> Inferno_18
{
  {   0.00000f,   0.00000f,   0.01569f },
  {   0.03922f,   0.02745f,   0.13333f },
  {   0.11765f,   0.04706f,   0.27059f },
  {   0.21961f,   0.03529f,   0.38431f },
  {   0.31765f,   0.05490f,   0.42353f },
  {   0.41176f,   0.08627f,   0.43137f },
  {   0.50196f,   0.12157f,   0.42353f },
  {   0.59608f,   0.15294f,   0.40000f },
  {   0.69020f,   0.19216f,   0.35686f },
  {   0.77647f,   0.23922f,   0.30196f },
  {   0.85098f,   0.30196f,   0.23922f },
  {   0.91373f,   0.38039f,   0.16863f },
  {   0.95686f,   0.47451f,   0.09412f },
  {   0.98039f,   0.58039f,   0.02745f },
  {   0.98824f,   0.69020f,   0.07843f },
  {   0.97255f,   0.80392f,   0.21569f },
  {   0.94902f,   0.91765f,   0.41176f },
  {   0.98824f,   1.00000f,   0.64314f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
