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
static const std::vector<vivid::srgb_t> Plasma_14
{
  {   0.05098f,   0.03137f,   0.52941f },
  {   0.21961f,   0.01569f,   0.60392f },
  {   0.34510f,   0.00392f,   0.64314f },
  {   0.46667f,   0.00392f,   0.65882f },
  {   0.57255f,   0.05882f,   0.63922f },
  {   0.67451f,   0.14902f,   0.58039f },
  {   0.76078f,   0.23529f,   0.50588f },
  {   0.83137f,   0.32157f,   0.43922f },
  {   0.89412f,   0.41176f,   0.36863f },
  {   0.94510f,   0.50588f,   0.30196f },
  {   0.98039f,   0.60784f,   0.23922f },
  {   0.99608f,   0.72157f,   0.17255f },
  {   0.98431f,   0.84314f,   0.14118f },
  {   0.94118f,   0.97647f,   0.12941f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
