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
static const std::vector<vivid::srgb_t> Lisbon_17
{
  {   0.90196f,   0.89804f,   1.00000f },
  {   0.73333f,   0.77647f,   0.89804f },
  {   0.56471f,   0.65490f,   0.80000f },
  {   0.40784f,   0.53725f,   0.70196f },
  {   0.25490f,   0.41569f,   0.59216f },
  {   0.14118f,   0.29804f,   0.45490f },
  {   0.08627f,   0.20000f,   0.30980f },
  {   0.06667f,   0.12157f,   0.18039f },
  {   0.09020f,   0.09804f,   0.09804f },
  {   0.15686f,   0.14902f,   0.10196f },
  {   0.26275f,   0.24706f,   0.15686f },
  {   0.37647f,   0.35294f,   0.22353f },
  {   0.49804f,   0.47059f,   0.29804f },
  {   0.62745f,   0.59608f,   0.39608f },
  {   0.75686f,   0.72941f,   0.52941f },
  {   0.87843f,   0.86275f,   0.68627f },
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
