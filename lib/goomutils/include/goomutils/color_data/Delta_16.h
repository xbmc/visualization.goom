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
static const std::vector<vivid::srgb_t> Delta_16
{
  {   0.06667f,   0.12549f,   0.25098f },
  {   0.14510f,   0.21176f,   0.47843f },
  {   0.10588f,   0.33725f,   0.61569f },
  {   0.13725f,   0.47059f,   0.63922f },
  {   0.22745f,   0.59608f,   0.67059f },
  {   0.42353f,   0.70980f,   0.70196f },
  {   0.67451f,   0.80784f,   0.77647f },
  {   0.89020f,   0.92157f,   0.87059f },
  {   0.95294f,   0.91373f,   0.66275f },
  {   0.84706f,   0.77255f,   0.37255f },
  {   0.66667f,   0.67451f,   0.12549f },
  {   0.43922f,   0.59216f,   0.02745f },
  {   0.19608f,   0.50196f,   0.12157f },
  {   0.04314f,   0.38824f,   0.17255f },
  {   0.09020f,   0.26275f,   0.15294f },
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
