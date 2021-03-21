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
static const std::vector<vivid::srgb_t> Acton_11
{
  {   0.18039f,   0.12941f,   0.30196f },
  {   0.28627f,   0.22353f,   0.39216f },
  {   0.40000f,   0.31373f,   0.48235f },
  {   0.52941f,   0.37647f,   0.55294f },
  {   0.65098f,   0.40000f,   0.58039f },
  {   0.76863f,   0.43137f,   0.60784f },
  {   0.83137f,   0.52549f,   0.67843f },
  {   0.83137f,   0.60784f,   0.73725f },
  {   0.83529f,   0.69804f,   0.80392f },
  {   0.86275f,   0.80000f,   0.87059f },
  {   0.90196f,   0.90196f,   0.94118f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
