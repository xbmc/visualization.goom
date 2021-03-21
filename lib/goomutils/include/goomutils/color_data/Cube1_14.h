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
static const std::vector<vivid::srgb_t> Cube1_14
{
  {   0.47059f,   0.00000f,   0.52157f },
  {   0.51373f,   0.07451f,   0.74118f },
  {   0.47843f,   0.29412f,   0.92157f },
  {   0.40000f,   0.45098f,   0.98039f },
  {   0.32549f,   0.58039f,   0.89804f },
  {   0.22745f,   0.69412f,   0.75294f },
  {   0.26275f,   0.78039f,   0.58431f },
  {   0.31373f,   0.84314f,   0.41569f },
  {   0.38824f,   0.90196f,   0.29020f },
  {   0.58824f,   0.92549f,   0.32549f },
  {   0.74902f,   0.92549f,   0.34902f },
  {   0.85098f,   0.88235f,   0.35686f },
  {   0.94118f,   0.76863f,   0.36863f },
  {   0.97647f,   0.58824f,   0.35686f },
};
// clang-format on

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif
