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
static const std::vector<vivid::srgb_t> Turbid_11
{
  {   0.91373f,   0.96471f,   0.67059f },
  {   0.85882f,   0.84706f,   0.52549f },
  {   0.81176f,   0.73725f,   0.40000f },
  {   0.76863f,   0.63137f,   0.30196f },
  {   0.70980f,   0.52941f,   0.25098f },
  {   0.63137f,   0.43922f,   0.23137f },
  {   0.54118f,   0.36863f,   0.22745f },
  {   0.44314f,   0.30588f,   0.21569f },
  {   0.33725f,   0.24314f,   0.18824f },
  {   0.23137f,   0.18431f,   0.15294f },
  {   0.13333f,   0.12157f,   0.10588f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
