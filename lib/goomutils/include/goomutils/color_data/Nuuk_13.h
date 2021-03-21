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
static const std::vector<vivid::srgb_t> Nuuk_13
{
  {   0.01961f,   0.34902f,   0.54902f },
  {   0.13333f,   0.37647f,   0.52157f },
  {   0.21961f,   0.41176f,   0.50980f },
  {   0.32549f,   0.46667f,   0.52157f },
  {   0.43529f,   0.52941f,   0.55294f },
  {   0.54118f,   0.59216f,   0.58431f },
  {   0.63137f,   0.65098f,   0.59608f },
  {   0.69020f,   0.69412f,   0.58039f },
  {   0.72941f,   0.72549f,   0.55294f },
  {   0.76471f,   0.76078f,   0.52157f },
  {   0.81961f,   0.81569f,   0.51765f },
  {   0.90980f,   0.90980f,   0.58431f },
  {   0.99608f,   0.99608f,   0.69804f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
