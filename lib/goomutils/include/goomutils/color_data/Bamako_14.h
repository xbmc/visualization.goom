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
static const std::vector<vivid::srgb_t> Bamako_14
{
  {   0.00000f,   0.25098f,   0.29804f },
  {   0.05490f,   0.28235f,   0.27059f },
  {   0.10196f,   0.30980f,   0.24314f },
  {   0.15294f,   0.34510f,   0.21176f },
  {   0.20784f,   0.38039f,   0.17647f },
  {   0.27059f,   0.41961f,   0.14118f },
  {   0.34118f,   0.46667f,   0.10196f },
  {   0.41961f,   0.51765f,   0.05490f },
  {   0.52157f,   0.55686f,   0.01176f },
  {   0.63137f,   0.58824f,   0.05882f },
  {   0.75686f,   0.67059f,   0.18039f },
  {   0.86275f,   0.76078f,   0.32941f },
  {   0.93333f,   0.83137f,   0.46275f },
  {   1.00000f,   0.89804f,   0.60000f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
