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
static const std::vector<vivid::srgb_t> Gray_18
{
  {   0.00000f,   0.00000f,   0.00000f },
  {   0.03137f,   0.03137f,   0.03137f },
  {   0.09412f,   0.09020f,   0.09020f },
  {   0.14902f,   0.14902f,   0.14510f },
  {   0.20392f,   0.20000f,   0.20000f },
  {   0.25490f,   0.25490f,   0.25098f },
  {   0.30980f,   0.30588f,   0.30588f },
  {   0.36078f,   0.36078f,   0.35686f },
  {   0.41569f,   0.41569f,   0.41176f },
  {   0.47059f,   0.47059f,   0.46667f },
  {   0.52941f,   0.52549f,   0.52549f },
  {   0.58824f,   0.58431f,   0.58431f },
  {   0.64706f,   0.64706f,   0.64314f },
  {   0.71373f,   0.70980f,   0.70588f },
  {   0.77647f,   0.77647f,   0.77255f },
  {   0.84706f,   0.84706f,   0.84314f },
  {   0.92157f,   0.92157f,   0.91765f },
  {   1.00000f,   1.00000f,   0.99216f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
