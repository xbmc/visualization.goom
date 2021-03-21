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
static const std::vector<vivid::srgb_t> Balance_14
{
  {   0.09412f,   0.10980f,   0.26275f },
  {   0.15686f,   0.21569f,   0.51765f },
  {   0.07451f,   0.34118f,   0.74510f },
  {   0.16863f,   0.49804f,   0.72941f },
  {   0.37255f,   0.62353f,   0.73333f },
  {   0.61961f,   0.73725f,   0.78039f },
  {   0.84706f,   0.86275f,   0.87059f },
  {   0.90980f,   0.84314f,   0.82353f },
  {   0.85098f,   0.66275f,   0.59608f },
  {   0.79608f,   0.48235f,   0.37647f },
  {   0.73725f,   0.30196f,   0.19608f },
  {   0.62353f,   0.10588f,   0.14902f },
  {   0.43922f,   0.05490f,   0.15294f },
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
